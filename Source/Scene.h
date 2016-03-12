#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;

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

