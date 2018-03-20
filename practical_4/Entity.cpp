#include "Entity.h"
#include "SystemRenderer.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

void Entity::move(const Vector2f &pos) { _position += pos; }

void Entity::Update(const float dt) {
	_shape->setPosition(_position);
}

void Entity::Render() {
	Renderer::queue(_shape.get());
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

void EntityManager::Update(const float dt) {
	for (shared_ptr<Entity> e : list) {
		e->Update(dt);
	}
}

void EntityManager::Render() {
	for (shared_ptr<Entity> e : list) {
		e->Render();
	}
}