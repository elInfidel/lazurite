#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Material.h"
#include <vector>
#include <string>
#include "Transform.h"

class Model
{
public:
	Model(const char* path);
	virtual ~Model();

	void Draw(const ShaderProgram& shaderProgram) const;

	Transform transform;
private:

	vector<Mesh> meshes;
	string directory;

	void LoadModel(string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Material LoadMaterial(aiMaterial* mat);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType::Type typeName);
};

