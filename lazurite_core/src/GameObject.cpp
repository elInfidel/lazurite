#include "GameObject.h"
#include "Component/AComponent.h"
#include <type_traits>

GameObject::GameObject() {
	this->AddComponent<Transform>();
}

GameObject::~GameObject() {
	componentList.clear();
}

void GameObject::SetActive(bool active) {
	_isActive = active;
}

bool GameObject::IsActive() const {
	return _isActive;
}

void  GameObject::SetName(const std::string name) {
	_name = name;
}

std::string  GameObject::GetName() const {
	return _name;
}

void GameObject::Tick(float deltaTime) {

	// Tick all components
	for (const auto& component : componentList) {
		if(component.second != nullptr && component.second.get()->IsActive())
			component.second.get()->Tick(deltaTime);
	}

	// Tick all game objects under this in the hierarchy
	auto children = this->GetComponent<Transform>().lock()->GetChildren();
	for (auto transform : children) {
		transform->gameObject->Tick(deltaTime);
	}

}