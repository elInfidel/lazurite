#pragma once
#include <string>
#include "Scene.h"

template <class T>
class AssetLoader {
	virtual T Load(std::string path) = 0;
};

class SceneLoader : public AssetLoader<std::shared_ptr<Scene>>{
public:
	virtual std::shared_ptr<Scene> Load(std::string path) = 0;
};