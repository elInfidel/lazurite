#pragma once
#include "Component/Transform.h"
#include <memory>
#include <vector>
#include <typeinfo>
#include <functional>
#include <map>
#include <string>
#include <iostream>

class AComponent;

class GameObject final
{
	typedef std::shared_ptr<AComponent> StrongComponentPtr;
	typedef std::weak_ptr<AComponent> WeakComponentPtr;
    typedef std::reference_wrapper<const std::type_info> ComponentID;

	std::string _name = "";
	bool _isActive = true;
	bool _isTicking = true;

	struct TypeComparator
	{
		bool operator()(const ComponentID& lhs, const ComponentID& rhs) const
		{
			return lhs.get().before(rhs.get());
		}
	};

	std::map<ComponentID, StrongComponentPtr, TypeComparator> componentList;

	void Tick(float deltaTime);

public:
	GameObject();
	~GameObject();

	void SetActive(const bool active);
	bool IsActive() const;

	void SetName(const std::string name);
	std::string GetName() const;

	// Adds the component T to this game object if the component doesn't already exist.
	template<class T>
	std::weak_ptr<T> AddComponent()
	{
		static_assert(std::is_base_of<AComponent, T>::value, "T not derived from AComponent");
		auto newComponent = std::pair<ComponentID, StrongComponentPtr>(typeid(T), std::make_shared<T>());
		newComponent.second->gameObject = this;
		componentList.insert(newComponent);
		return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(newComponent.second));
	}

	// Adds the component T to this game object if the component doesn't already exist.
	template<class T>
	std::weak_ptr<T> AddComponent(std::shared_ptr<T> existingComponent)
	{
		static_assert(std::is_base_of<AComponent, T>::value, "T not derived from AComponent");
		auto newComponent = std::pair<ComponentID, StrongComponentPtr>(typeid(T), existingComponent);
		newComponent.second->gameObject = this;
		componentList.insert(newComponent);
		return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(newComponent.second));
	}

	// Removes the component T from this game object if it exists.
	template<class T>
	void RemoveComponent()
	{
		static_assert(std::is_base_of<AComponent, T>::value, "T not derived from AComponent");
		auto it = componentList.find(typeid(T));
		if (it != componentList.end())
			componentList.erase(it);
	}

	// Returns a non owning pointer to the component T if it exists on this game object.
	template<class T>
	std::weak_ptr<T> GetComponent()
	{
		static_assert(std::is_base_of<AComponent, T>::value, "T not derived from AComponent");

		if (componentList.empty()) {
			return std::weak_ptr<T>();
		}

		auto it = componentList.find(typeid(T));
		if (it != componentList.end())
		{
			std::shared_ptr<T> downcast = std::dynamic_pointer_cast<T>(it->second);
			return std::weak_ptr<T>(downcast);
		}
		return std::weak_ptr<T>();
	}

	// Returns true when the component T is contained within this game object.
	template<class T>
	bool ContainsComponent()
	{
		static_assert(std::is_base_of<AComponent, T>::value, "T not derived from AComponent");
		return componentList.find(typeid(T)) != componentList.end();
	}
};

