#pragma once
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

class Component; // Forward declare

class Entity {
protected:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	float _rotation;
	bool _alive; // Is updated
	bool _visible; // Is rendered
	bool _forDeletion; // Is for deletion
public:
	Entity();
	virtual ~Entity() = default;
	virtual void Update(const double &dt);
	virtual void Render();

	const sf::Vector2f &getPosition() const;
	void setPosition(const sf::Vector2f &_position);
	bool forDeletion() const;
	float getRotation() const;
	void setRotation(float _rotation);
	bool isAlive() const;
	void setAlive(bool _alive);
	void setForDelete(bool _forDelete);
	bool isVisible() const;
	void setVisible(bool _visible);

	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "T != component");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}
};

class Component {
protected:
	Entity *const _parent;
	bool _forDeletion; // Should be removed
	explicit Component(Entity *const p);

public:
	Component() = delete;
	bool forDeletion() const;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual ~Component() = default;
};