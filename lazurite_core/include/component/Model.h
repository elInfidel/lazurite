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
#include <component\Camera.h>
#include <component\Transform.h>

class Model : public AComponent
{
	vector<Mesh> meshes;
	string directory;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	MaterialBase* LoadMaterial(aiMaterial* mat);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType::Type typeName);

public:

	Model();

	virtual void Tick(float deltaTime) {};
	void Draw(Camera& camera, Transform& camTransform, Transform& modelTransform) const;

	void LoadModel(string path);
};