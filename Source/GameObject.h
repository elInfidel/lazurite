#pragma once
#include <memory>
#include <vector>
#include <typeinfo>
#include <map>

class AComponent;

class GameObject final
{
	bool _isActive = true;
	bool _isTicking = true;

	std::map<std::type_info, std::shared_ptr<AComponent>> _components;
	void Tick(float deltaTime);

public:
	GameObject();
	~GameObject();

	void SetActive(bool active);
	bool IsActive();

	void SetTick(bool tick);
	bool IsTicking();

	// Components
	template<class T> void AddComponent();
	template<class T> void RemoveComponent();
	template<class T> std::weak_ptr<T> GetComponent();
};

