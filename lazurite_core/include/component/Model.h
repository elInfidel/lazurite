#pragma once

#include "AComponent.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Mesh.h"
#include "GameObject.h"
#include "component\Camera.h"
#include "component\Transform.h"
#include <vector>
#include <string>

class MaterialBase;

// We should pull this code into some sort of Asset loading service
class Model
{
	static void ProcessNode(std::shared_ptr<GameObject> parent, aiNode* node, const aiScene* scene);
	static std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static MaterialBase* LoadMaterial(aiMaterial* mat);
	static vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType::Type typeName);

public:
	static std::shared_ptr<GameObject> Load(string path);
};