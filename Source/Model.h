#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include <vector>
#include <string>

class Model
{
public:
	Model(const char* path);
	virtual ~Model();

	void Draw(const ShaderProgram& shaderProgram) const;

private:

	vector<Mesh> meshes;
	string directory;

	void LoadModel(string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

