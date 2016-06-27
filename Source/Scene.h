#pragma once
#include <vector>
#include "glm/glm.hpp"

using namespace std;
using glm::vec3;
using glm::quat;

class GameObject;

class Scene
{
	friend class Engine;
public:
	GameObject* InstantiateGameObject();
	GameObject* InstantiateGameObject(vec3 position, quat rotation);

private:
	Scene();
	virtual ~Scene();

	vector<GameObject*> sceneGraph;
	void Update(float deltaTime);
};

