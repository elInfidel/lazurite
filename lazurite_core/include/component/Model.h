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
	static GameObject* ProcessNode(string path, aiNode* node, const aiScene* scene);
	static std::shared_ptr<Mesh> ProcessMesh(string path, aiMesh* mesh, const aiScene* scene);
	static MaterialBase* LoadMaterial(string path, aiMaterial* mat);
	static vector<Texture> LoadMaterialTextures(string path, aiMaterial* mat, aiTextureType type, TextureType::Type typeName);

public:
	static std::shared_ptr<GameObject> Load(string path);
};