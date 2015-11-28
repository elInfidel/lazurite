#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();

private:
	vector<GameObject*> sceneGraph;

};

