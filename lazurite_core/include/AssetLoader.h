#pragma once
#include <string>

template <class T>
class AssetLoader {
	virtual T Load(std::string path) = 0;
};

class SceneLoader : public AssetLoader<std::shared_ptr<GameObject>>{
protected:
	virtual GameObject* ProcessNode(string path) = 0;
	virtual std::shared_ptr<Mesh> ProcessMesh(string path) = 0;
	virtual MaterialBase* LoadMaterial(string path) = 0;
	virtual vector<Texture> LoadMaterialTextures(string path, TextureType::Type typeName) = 0;
public:
	virtual std::shared_ptr<GameObject> Load(std::string path) = 0;
};