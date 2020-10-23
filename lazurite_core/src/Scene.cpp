#include "scene.h"

void Scene::AppendGameObject(std::shared_ptr<GameObject> object) {
	this->root.push_back(object);
}

void Scene::Render() {
	for (auto obj : this->root) {
		auto transform = obj->GetComponent<Transform>().lock();
	}
}