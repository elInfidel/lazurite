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

	struct TypeComparator
	{
		bool operator()(const ComponentID& lhs, const ComponentID& rhs) const
		{
			return lhs.get().before(rhs.get());
		}
	};

	std::map<ComponentID, StrongComponentPtr, TypeComparator> _components;

	void Tick(float deltaTime);

public:
	GameObject();
	~GameObject();

	void SetActive(bool active);
	bool IsActive() const;

	void SetTick(bool tick);
	bool IsTicking() const;

	/// Adds the component T to this game object if the component doesn't already exist.
	template<class T>
	void AddComponent()
	{
		_components.insert(std::pair<ComponentID, StrongComponentPtr>(typeid(T), std::make_shared<T>()));
	}

	/// Removes the component T from this game object if it exists.
	template<class T>
	void RemoveComponent()
	{
		auto it = _components.find(typeid(T));
		if (it != _components.end())
			_components.erase(it);
	}

	/// Returns a non owning pointer to the component T if it exists on this game object.
	template<class T>
	std::weak_ptr<T> GetComponent()
	{
		auto it = _components.find(typeid(T));
		if (it != _components.end())
		{
			std::shared_ptr<T> downcast = std::dynamic_pointer_cast<T>(it->second);
			return std::weak_ptr<T>(downcast);
		}

			return std::weak_ptr<T>();
	}

	/// Returns true when the component T is contained within this game object.
	template<class T>
	bool ContainsComponent()
	{
		return _components.find(typeid(T)) != _components.end();
	}
};

