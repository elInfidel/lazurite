#include "Scene.h"

Scene* Scene::currentScene;

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Update(float deltaTime)
{
	// For now we just update all objects as opposed to filtering them down.
	for (shared_ptr<GameObject> go : sceneGraph)
	{
		go->Update(deltaTime);
	}
}

shared_ptr<GameObject> Scene::InstantiateGameObject()
{
	shared_ptr<GameObject> go;

	if (currentScene == nullptr) return go;

	go = make_shared<GameObject>();
	currentScene->sceneGraph.push_back(go);

	return go;
}

shared_ptr<GameObject> Scene::InstantiateGameObject(vec3 position, quat rotation)
{
	//TODO
	return shared_ptr<GameObject>();
}
