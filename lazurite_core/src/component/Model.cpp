#include "component/Model.h"
#include "rendering/Material.h"
#include <iostream>

std::shared_ptr<GameObject> Model::Load(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes
	);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return std::shared_ptr<GameObject>(nullptr);
	}
	return std::shared_ptr<GameObject>(Model::ProcessNode(path, scene->mRootNode, scene));
}

GameObject* Model::ProcessNode(string path, aiNode* node, const aiScene* scene)
{
	auto obj = new GameObject();
	auto transform = obj->GetComponent<Transform>().lock();

	obj->SetName(node->mName.C_Str());

	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		auto mesh = scene->mMeshes[node->mMeshes[i]];
		auto newMesh = Model::ProcessMesh(path, mesh, scene);
		obj->AddComponent<Mesh>(newMesh);
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		auto childObject = Model::ProcessNode(path, node->mChildren[i], scene);
		auto childTransform = childObject->GetComponent<Transform>().lock();
		childTransform->SetParent(transform);
		transform->AddChild(childTransform);
	}

	return obj;
}

std::shared_ptr<Mesh> Model::ProcessMesh(string path, aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	MaterialBase* material;

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
		material = LoadMaterial(path, scene->mMaterials[mesh->mMaterialIndex]);
	}

	return std::shared_ptr<Mesh>(new Mesh(vertices, indices, material));
}

MaterialBase* Model::LoadMaterial(string path, aiMaterial* mat)
{
	MaterialBase* material;

	// TODO: Check presence of PBR related properties to
	// build relevant material

	material = new PBRMaterial();

	// Load textures
	// TODO: Comment PBR textures

	/* The texture is an albedo map
	*
	*  Used most commonly in physically based rendering. Very similar to the diffuse map
	*  however the albedo stores no lighting information and purely represents the surface color at some given position.
	*
	*/
	vector<Texture> albedoMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_BASE_COLOR, TextureType::Albedo);
	material->textures.insert(material->textures.end(), albedoMaps.begin(), albedoMaps.end());

	vector<Texture> metallicMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_METALNESS, TextureType::Metallic);
	material->textures.insert(material->textures.end(), metallicMaps.begin(), metallicMaps.end());

	vector<Texture> roughnessMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_DIFFUSE_ROUGHNESS, TextureType::Roughness);
	material->textures.insert(material->textures.end(), roughnessMaps.begin(), roughnessMaps.end());

	vector<Texture> aoMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_AMBIENT_OCCLUSION, TextureType::AmbientOcclusion);
	material->textures.insert(material->textures.end(), aoMaps.begin(), aoMaps.end());

	/* The texture is combined with the result of the diffuse
	*  lighting equation.
	*/
	vector<Texture> diffuseMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_DIFFUSE, TextureType::Diffuse);
	material->textures.insert(material->textures.end(), diffuseMaps.begin(), diffuseMaps.end());


	/** The texture is combined with the result of the specular
	*  lighting equation.
	*/
	vector<Texture> specularMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_SPECULAR, TextureType::Specular);
	material->textures.insert(material->textures.end(), specularMaps.begin(), specularMaps.end());

	/** The texture is combined with the result of the ambient
	*  lighting equation.
	*/
	vector<Texture> ambientMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_AMBIENT, TextureType::Ambient);
	material->textures.insert(material->textures.end(), ambientMaps.begin(), ambientMaps.end());

	/** The texture is added to the result of the lighting
	*  calculation. It isn't influenced by incoming light.
	*/
	vector<Texture> emissiveMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_EMISSIVE, TextureType::Emissive);
	material->textures.insert(material->textures.end(), emissiveMaps.begin(), emissiveMaps.end());

	/** The texture is a height map.
	*
	*  By convention, higher gray-scale values stand for
	*  higher elevations from the base height.
	*/
	vector<Texture> heightMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_HEIGHT, TextureType::Height);
	material->textures.insert(material->textures.end(), heightMaps.begin(), heightMaps.end());

	/** The texture is a (tangent space) normal-map.
	*
	*  Again, there are several conventions for tangent-space
	*  normal maps. Assimp does (intentionally) not
	*  distinguish here.
	*/
	vector<Texture> normalMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_NORMALS, TextureType::Normal);
	material->textures.insert(material->textures.end(), normalMaps.begin(), normalMaps.end());

	/** The texture defines the glossiness of the material->
	*
	*  The glossiness is in fact the exponent of the specular
	*  (phong) lighting equation. Usually there is a conversion
	*  function defined to map the linear color values in the
	*  texture to a suitable exponent. Have fun.
	*
	*  NOTE: We treat these as roughness maps moving forward.
	*
	*/
	vector<Texture> shininessMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_SHININESS, TextureType::Roughness);
	material->textures.insert(material->textures.end(), shininessMaps.begin(), shininessMaps.end());

	/** The texture defines per-pixel opacity.
	*
	*  Usually 'white' means opaque and 'black' means
	*  'transparency'. Or quite the opposite. Have fun.
	*/
	vector<Texture> opacityMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_OPACITY, TextureType::Opacity);
	material->textures.insert(material->textures.end(), opacityMaps.begin(), opacityMaps.end());

	/** Displacement texture
	*
	*  The exact purpose and format is application-dependent.
	*  Higher color values stand for higher vertex displacements.
	*/
	vector<Texture> displacementMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_DISPLACEMENT, TextureType::Displacement);
	material->textures.insert(material->textures.end(), displacementMaps.begin(), displacementMaps.end());

	/** Lightmap texture (aka Ambient Occlusion)
	*
	*  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
	*  covered by this material property. The texture contains a
	*  scaling value for the final color value of a pixel. Its
	*  intensity is not affected by incoming light.
	*/
	vector<Texture> lightMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_LIGHTMAP, TextureType::Lightmap);
	material->textures.insert(material->textures.end(), lightMaps.begin(), lightMaps.end());

	/** Reflection texture
	*
	* Contains the color of a perfect mirror reflection.
	* Rarely used, almost never for real-time applications.
	*/
	vector<Texture> reflectionMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_REFLECTION, TextureType::Reflection);
	material->textures.insert(material->textures.end(), reflectionMaps.begin(), reflectionMaps.end());

	/** Unknown texture
	*
	*  A texture reference that does not match any of the definitions
	*  above is considered to be 'unknown'. It is still imported,
	*  but is excluded from any further postprocessing.
	*/
	vector<Texture> unknownMaps = Model::LoadMaterialTextures(path, mat, aiTextureType_UNKNOWN, TextureType::Unknown);
	material->textures.insert(material->textures.end(), unknownMaps.begin(), unknownMaps.end());

	return material;
}

vector<Texture> Model::LoadMaterialTextures(string path, aiMaterial* mat, aiTextureType type, TextureType::Type typeName)
{
	vector<Texture> textures;

	for (size_t i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString string;
		mat->GetTexture(type, (unsigned int)i, &string);
		Texture texture;
		texture.LoadTexture(path.substr(0, path.find_last_of('/')), string.C_Str(), typeName);
		textures.push_back(texture);
	}

	return textures;
}