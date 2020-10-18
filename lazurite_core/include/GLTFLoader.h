#pragma once

#include "component/AComponent.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Mesh.h"
#include "GameObject.h"
#include "AssetLoader.h"
#include "component\Camera.h"
#include "component\Transform.h"
#include <vector>

class MaterialBase;

class GLTFLoader : public SceneLoader
{
	GameObject* ProcessNode(string path);
	std::shared_ptr<Mesh> ProcessMesh(string path);
	MaterialBase* LoadMaterial(string path);
	vector<Texture> LoadMaterialTextures(string path, TextureType::Type typeName);
public:
	std::shared_ptr<GameObject> Load(string path);
};