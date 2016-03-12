#include "Model.h"
#include <iostream>

using namespace Assimp;

Model::Model(const char* path)
{
	LoadModel(path);
}

Model::~Model()
{
}

void Model::LoadModel(string path)
{
	Importer importer;
	//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	const aiScene* scene = importer.ReadFile(path, aiProcess_OptimizeMeshes | aiProcess_GenSmoothNormals | aiProcess_OptimizeGraph | aiProcess_Triangulate | aiProcess_FlipUVs);
	//const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Quality);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		// TODO: Setup Logger class
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of('/'));
	this->ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	Material material;

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		
		// Vertex positions
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		// Vertex colors
		if (mesh->HasVertexColors(0))
		{
			vertex.color.r = mesh->mColors[0][i].r;
			vertex.color.g = mesh->mColors[0][i].g;
			vertex.color.b = mesh->mColors[0][i].b;
			// TODO: Alpha support?
		}

		// Vertex normals
		if (mesh->HasNormals())
		{
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;
		}

		//Vertex tangent / bitangent
		if (mesh->HasTangentsAndBitangents())
		{
			vertex.tangent.x = mesh->mTangents[i].x;
			vertex.tangent.y = mesh->mTangents[i].y;
			vertex.tangent.z = mesh->mTangents[i].z;

			vertex.bitangent.x = mesh->mBitangents[i].x;
			vertex.bitangent.y = mesh->mBitangents[i].y;
			vertex.bitangent.z = mesh->mBitangents[i].z;
		}

		// Vertex weights
		//if (mesh->HasBones())
		//{
		//	vertex.weights.x 
		//}

		// Vertex texcoords
		if (mesh->HasTextureCoords(0))
		{
			vertex.texCoord1.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord1.y = mesh->mTextureCoords[0][i].y;
		}

		if (mesh->HasTextureCoords(1))
		{
			vertex.texCoord2.x = mesh->mTextureCoords[1][i].x;
			vertex.texCoord2.y = mesh->mTextureCoords[1][i].y;
		}

		vertices.push_back(vertex);
	}

	// Vertex indices
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// TODO: Load texture data into some material class
	if (mesh->mMaterialIndex >= 0)
	{
		material = LoadMaterial(scene->mMaterials[mesh->mMaterialIndex]);
	}

	return Mesh(vertices, indices, material);
}

Material Model::LoadMaterial(aiMaterial* mat)
{
	Material material;

	// Load material properties
	aiColor3D ambient(1.f, 1.f, 1.f);
	mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	aiColor3D diffuse(1.f, 1.f, 1.f);
	mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	aiColor3D specular(0.f, 0.f, 0.f);
	mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);

	material.properties.ambient.r = ambient.r;
	material.properties.ambient.g = ambient.g;
	material.properties.ambient.b = ambient.b;

	material.properties.diffuse.r = diffuse.r;
	material.properties.diffuse.g = diffuse.g;
	material.properties.diffuse.b = diffuse.b;

	material.properties.specular.r = specular.r;
	material.properties.specular.g = specular.g;
	material.properties.specular.b = specular.b;

	// Load textures

	/** The texture is combined with the result of the diffuse
	*  lighting equation.
	*/
	vector<Texture> diffuseMaps = this->LoadMaterialTextures(mat, aiTextureType_DIFFUSE, TextureType::Diffuse);
	material.textures.insert(material.textures.end(), diffuseMaps.begin(), diffuseMaps.end());


	/** The texture is combined with the result of the specular
	*  lighting equation.
	*/
	vector<Texture> specularMaps = this->LoadMaterialTextures(mat, aiTextureType_SPECULAR, TextureType::Specular);
	material.textures.insert(material.textures.end(), specularMaps.begin(), specularMaps.end());

	/** The texture is combined with the result of the ambient
	*  lighting equation.
	*/
	vector<Texture> ambientMaps = this->LoadMaterialTextures(mat, aiTextureType_AMBIENT, TextureType::Ambient);
	material.textures.insert(material.textures.end(), ambientMaps.begin(), ambientMaps.end());

	/** The texture is added to the result of the lighting
	*  calculation. It isn't influenced by incoming light.
	*/
	vector<Texture> emissiveMaps = this->LoadMaterialTextures(mat, aiTextureType_EMISSIVE, TextureType::Emissive);
	material.textures.insert(material.textures.end(), emissiveMaps.begin(), emissiveMaps.end());

	/** The texture is a height map.
	*
	*  By convention, higher gray-scale values stand for
	*  higher elevations from the base height.
	*/
	vector<Texture> heightMaps = this->LoadMaterialTextures(mat, aiTextureType_HEIGHT, TextureType::Height);
	material.textures.insert(material.textures.end(), heightMaps.begin(), heightMaps.end());

	/** The texture is a (tangent space) normal-map.
	*
	*  Again, there are several conventions for tangent-space
	*  normal maps. Assimp does (intentionally) not
	*  distinguish here.
	*/
	vector<Texture> normalMaps = this->LoadMaterialTextures(mat, aiTextureType_NORMALS, TextureType::Normal);
	material.textures.insert(material.textures.end(), normalMaps.begin(), normalMaps.end());

	/** The texture defines the glossiness of the material.
	*
	*  The glossiness is in fact the exponent of the specular
	*  (phong) lighting equation. Usually there is a conversion
	*  function defined to map the linear color values in the
	*  texture to a suitable exponent. Have fun.
	*/
	vector<Texture> shininessMaps = this->LoadMaterialTextures(mat, aiTextureType_SHININESS, TextureType::Shininess);
	material.textures.insert(material.textures.end(), shininessMaps.begin(), shininessMaps.end());

	/** The texture defines per-pixel opacity.
	*
	*  Usually 'white' means opaque and 'black' means
	*  'transparency'. Or quite the opposite. Have fun.
	*/
	vector<Texture> opacityMaps = this->LoadMaterialTextures(mat, aiTextureType_OPACITY, TextureType::Opacity);
	material.textures.insert(material.textures.end(), opacityMaps.begin(), opacityMaps.end());

	/** Displacement texture
	*
	*  The exact purpose and format is application-dependent.
	*  Higher color values stand for higher vertex displacements.
	*/
	vector<Texture> displacementMaps = this->LoadMaterialTextures(mat, aiTextureType_DISPLACEMENT, TextureType::Displacement);
	material.textures.insert(material.textures.end(), displacementMaps.begin(), displacementMaps.end());

	/** Lightmap texture (aka Ambient Occlusion)
	*
	*  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
	*  covered by this material property. The texture contains a
	*  scaling value for the final color value of a pixel. Its
	*  intensity is not affected by incoming light.
	*/
	vector<Texture> lightMaps = this->LoadMaterialTextures(mat, aiTextureType_LIGHTMAP, TextureType::Lightmap);
	material.textures.insert(material.textures.end(), lightMaps.begin(), lightMaps.end());

	/** Reflection texture
	*
	* Contains the color of a perfect mirror reflection.
	* Rarely used, almost never for real-time applications.
	*/
	vector<Texture> reflectionMaps = this->LoadMaterialTextures(mat, aiTextureType_REFLECTION, TextureType::Reflection);
	material.textures.insert(material.textures.end(), reflectionMaps.begin(), reflectionMaps.end());

	/** Unknown texture
	*
	*  A texture reference that does not match any of the definitions
	*  above is considered to be 'unknown'. It is still imported,
	*  but is excluded from any further postprocessing.
	*/
	vector<Texture> unknownMaps = this->LoadMaterialTextures(mat, aiTextureType_UNKNOWN, TextureType::Unknown);
	material.textures.insert(material.textures.end(), unknownMaps.begin(), unknownMaps.end());

	return material;
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType::Type typeName)
{
	// TODO: May move this to some material class
	vector<Texture> textures;

	for (size_t i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString string;
		mat->GetTexture(type, i, &string);

		Texture texture;
		texture.LoadTexture(this->directory, string.C_Str(), typeName);
		textures.push_back(texture);
	}

	return textures;
}

void Model::Draw(const ShaderProgram& shaderProgram) const
{
	for (unsigned int i = 0; i < this->meshes.size(); ++i)
	{
		this->meshes[i].Draw(shaderProgram);
	}
}