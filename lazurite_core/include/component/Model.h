#pragma once

#include "AComponent.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Mesh.h"
#include "rendering/Material.h"
#include <vector>
#include <string>

class Model : public AComponent
{
	string directory;

	vector<Mesh*> meshes;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	MaterialBase* LoadMaterial(aiMaterial* mat);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType::Type typeName);

public:

	virtual void Tick(float deltaTime) {};
	void Draw(const mat4& view, const mat4& projection, const mat4& model);

	void LoadModel(string path);
};