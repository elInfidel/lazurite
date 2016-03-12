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

private:
	static Scene* scene;

	vector<GameObject*> sceneGraph;
	void Update(float deltaTime);

};

