#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto go : sceneGraph)
		delete go;

	sceneGraph.clear();
}

void Scene::Update(float deltaTime)
{
	for (auto go : sceneGraph)
	{
		if(go->IsActive())
			go->Update(deltaTime);
	}
}

GameObject* Scene::InstantiateGameObject()
{
	GameObject* go = new GameObject();
	sceneGraph.push_back(go);

	return go;
}

GameObject* Scene::InstantiateGameObject(vec3 position, quat rotation)
{
	GameObject* go = InstantiateGameObject();

	// WILL NOT WORK??
	//go->AddComponent(Transform);
	//go->GetComponent<Transform>()->SetTranslation(position);
	//go->GetComponent<Transform>()->SetRotation(rotation);

	return go;
}
