#include "Entity.h"
using namespace std;
using namespace sf;

void EntityManager::Update(const float dt) {
	for (shared_ptr<Entity> e : list) {
		e->Update(dt);
	}
}

void EntityManager::Render(RenderWindow &window) {
	for (shared_ptr<Entity> e : list) {
		e->Render(window);
	}
}

const Vector2f Entity::getPosition() { return _position; }

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

void Entity::move(const Vector2f &pos) { _position += pos; }

void Entity::Update(const float dt) {
	_shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}