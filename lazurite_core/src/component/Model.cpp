#include "component/Model.h"
#include "component/Camera.h"
#include <iostream>

void Model::LoadModel(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_OptimizeMeshes | aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of('/'));
	this->ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	std::cout << "Processing " << node->mNumMeshes << " nodes" << std::endl;
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

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

	if (mesh->mMaterialIndex >= 0)
	{
		material = LoadMaterial(scene->mMaterials[mesh->mMaterialIndex]);
	}

	return new Mesh(vertices, indices, material);
}

MaterialBase* Model::LoadMaterial(aiMaterial* mat)
{
	PBRMaterial* material = new PBRMaterial();

	vector<Texture> albedoMaps = this->LoadMaterialTextures(mat, aiTextureType_BASE_COLOR, TextureType::Diffuse);
	material->textures.insert(material->textures.end(), albedoMaps.begin(), albedoMaps.end());

	vector<Texture> metallicMaps = this->LoadMaterialTextures(mat, aiTextureType_METALNESS, TextureType::Diffuse);
	material->textures.insert(material->textures.end(), metallicMaps.begin(), metallicMaps.end());

	vector<Texture> roughnessMaps = this->LoadMaterialTextures(mat, aiTextureType_DIFFUSE_ROUGHNESS, TextureType::Diffuse);
	material->textures.insert(material->textures.end(), roughnessMaps.begin(), roughnessMaps.end());

	vector<Texture> aoMaps = this->LoadMaterialTextures(mat, aiTextureType_AMBIENT_OCCLUSION, TextureType::Diffuse);
	material->textures.insert(material->textures.end(), aoMaps.begin(), aoMaps.end());

	vector<Texture> diffuseMaps = this->LoadMaterialTextures(mat, aiTextureType_DIFFUSE, TextureType::Diffuse);
	material->textures.insert(material->textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	vector<Texture> specularMaps = this->LoadMaterialTextures(mat, aiTextureType_SPECULAR, TextureType::Specular);
	material->textures.insert(material->textures.end(), specularMaps.begin(), specularMaps.end());

	vector<Texture> ambientMaps = this->LoadMaterialTextures(mat, aiTextureType_AMBIENT, TextureType::Ambient);
	material->textures.insert(material->textures.end(), ambientMaps.begin(), ambientMaps.end());

	vector<Texture> emissiveMaps = this->LoadMaterialTextures(mat, aiTextureType_EMISSIVE, TextureType::Emissive);
	material->textures.insert(material->textures.end(), emissiveMaps.begin(), emissiveMaps.end());

	vector<Texture> heightMaps = this->LoadMaterialTextures(mat, aiTextureType_HEIGHT, TextureType::Height);
	material->textures.insert(material->textures.end(), heightMaps.begin(), heightMaps.end());

	vector<Texture> normalMaps = this->LoadMaterialTextures(mat, aiTextureType_NORMALS, TextureType::Normal);
	material->textures.insert(material->textures.end(), normalMaps.begin(), normalMaps.end());

	vector<Texture> shininessMaps = this->LoadMaterialTextures(mat, aiTextureType_SHININESS, TextureType::Shininess);
	material->textures.insert(material->textures.end(), shininessMaps.begin(), shininessMaps.end());

	vector<Texture> opacityMaps = this->LoadMaterialTextures(mat, aiTextureType_OPACITY, TextureType::Opacity);
	material->textures.insert(material->textures.end(), opacityMaps.begin(), opacityMaps.end());

	vector<Texture> displacementMaps = this->LoadMaterialTextures(mat, aiTextureType_DISPLACEMENT, TextureType::Displacement);
	material->textures.insert(material->textures.end(), displacementMaps.begin(), displacementMaps.end());

	vector<Texture> lightMaps = this->LoadMaterialTextures(mat, aiTextureType_LIGHTMAP, TextureType::Lightmap);
	material->textures.insert(material->textures.end(), lightMaps.begin(), lightMaps.end());

	vector<Texture> reflectionMaps = this->LoadMaterialTextures(mat, aiTextureType_REFLECTION, TextureType::Reflection);
	material->textures.insert(material->textures.end(), reflectionMaps.begin(), reflectionMaps.end());

	vector<Texture> unknownMaps = this->LoadMaterialTextures(mat, aiTextureType_UNKNOWN, TextureType::Unknown);
	material->textures.insert(material->textures.end(), unknownMaps.begin(), unknownMaps.end());

	return material;
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType::Type typeName)
{
	vector<Texture> textures;

	for (size_t i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString string;
		mat->GetTexture(type, (unsigned int)i, &string);

		Texture texture;
		texture.LoadTexture(this->directory, string.C_Str(), typeName);
		textures.push_back(texture);
	}

	return textures;
}

void Model::Draw(const mat4& view, const mat4& projection, const mat4& model)
{
	for (unsigned int i = 0; i < this->meshes.size(); ++i) {
		this->meshes[i]->Draw(view, projection, model);
	}
}