#pragma once
#include "Component/Transform.h"
#include <memory>
#include <vector>
#include <typeinfo>
#include <functional>
#include <map>

class AComponent;

class GameObject final
{
	typedef std::shared_ptr<AComponent> StrongComponentPtr;
	typedef std::weak_ptr<AComponent> WeakComponentPtr;
	typedef std::reference_wrapper<const std::type_info> ComponentID;

	bool _isActive = true;
	bool _isTicking = true;

	struct ComponentEqualTo 
	{
		bool operator()(ComponentID lhs, ComponentID rhs) const
		{
			return lhs.get() == rhs.get();
		}
	};

	std::map<ComponentID, StrongComponentPtr, ComponentEqualTo> _components;

	void Tick(float deltaTime);

public:
	GameObject();
	~GameObject();

	// State
	void SetActive(bool active);
	bool IsActive();

	void SetTick(bool tick);
	bool IsTicking();

	Transform& GetTransform();

	// Components
	template<class T> void AddComponent();
	template<class T> void RemoveComponent();
	template<class T> std::weak_ptr<T> GetComponent();
};

