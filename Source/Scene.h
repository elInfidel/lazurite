#pragma once
#include <vector>
#include "GameObject.h"
#include "glm/glm.hpp"

using namespace std;
using glm::vec3;
using glm::quat;

class Scene
{
	friend class Application;
public:
	Scene();
	virtual ~Scene();

	static shared_ptr<GameObject> InstantiateGameObject();
	static shared_ptr<GameObject> InstantiateGameObject(vec3 position, quat rotation);

private:
	static Scene* currentScene;

	vector<shared_ptr<GameObject>> sceneGraph;
	void Update(float deltaTime);
};

