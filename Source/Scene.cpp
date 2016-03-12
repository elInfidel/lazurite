#include "Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Update(float deltaTime)
{
	// For now we just update all objects as opposed to filtering them down.
	for (GameObject* go : sceneGraph)
	{
		go->Update(deltaTime);
	}
}
