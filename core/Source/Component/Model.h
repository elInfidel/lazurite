#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "../Rendering/ShaderProgram.h"
#include <vector>
#include <string>
#include "AComponent.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"

class Model : public AComponent
{
	vector<Mesh> meshes;
	string directory;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Material LoadMaterial(aiMaterial* mat);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType::Type typeName);

public:

	Model();

	virtual void Tick(float deltaTime) {};
	void Draw(const ShaderProgram& shaderProgram) const;

	void LoadModel(string path);
};