#pragma once

#include "component/AComponent.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Mesh.h"
#include "GameObject.h"
#include "AssetLoader.h"
#include "component\Camera.h"
#include "component\Transform.h"
#include "gltf.h"
#include "Scene.h"
#include "rendering/Material.h"
#include <vector>

class GLTFLoader : public SceneLoader
{
	std::shared_ptr<Scene> ProcessScene(const GLTFFile& const file, const GLTFScene& const scene);
	std::shared_ptr<GameObject> ProcessNode(const GLTFFile& constfile , const GLTFNode& const node);
	std::shared_ptr<Mesh> ProcessMesh(const GLTFFile& const file, const GLTFMesh& const mesh);
	std::shared_ptr<MaterialBase> ProcessMaterial(const GLTFFile& const file, const GLTFMaterial& const material);
	vector<Texture> LoadMaterialTextures(string path, TextureType::Type typeName);
public:
	std::shared_ptr<Scene> Load(string path);
};