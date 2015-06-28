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
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

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
	vector<Texture>textures;

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

	// TODO: Load material data into some material class
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = this->LoadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = this->LoadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	// TODO: May move this to some material class
	vector<Texture> textures;

	for (int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString string;
		mat->GetTexture(type, i, &string);

		Texture texture;
		texture.LoadTexture(string.C_Str());
		texture.typeName = typeName;
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