#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

class Scene {
	std::vector<std::shared_ptr<GameObject>> root;
public:
	void AppendGameObject(std::shared_ptr<GameObject> object);
	void Render();
};