#pragma once

#include "component/AComponent.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Mesh.h"
#include "GameObject.h"
#include "AssetLoader.h"
#include "component\Camera.h"
#include "component\Transform.h"
#include <vector>
#include <string>

class MaterialBase;

class SceneLoader : public AssetLoader<std::shared_ptr<GameObject>>
{
	GameObject* ProcessNode(string path, aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> ProcessMesh(string path, aiMesh* mesh, const aiScene* scene);
	MaterialBase* LoadMaterial(string path, aiMaterial* mat);
	vector<Texture> LoadMaterialTextures(string path, aiMaterial* mat, aiTextureType type, TextureType::Type typeName);
public:
	std::shared_ptr<GameObject> Load(string path);
};