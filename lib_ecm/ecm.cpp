#include "ecm.h"

using namespace std;
using namespace sf;

Entity::Entity() {
	_position = Vector2f(0.0f, 0.0f);
	_alive = true;
	_visible = true;
	_forDeletion = false;
}

void Entity::Update(const double &dt){
	for (shared_ptr<Component> c : _components) {
		c->Update(dt);
	}
}

void Entity::Render() {
	for (shared_ptr<Component> c : _components) {
		c->Render();
	}
}

const Vector2f &Entity::getPosition() const{
	return _position;
}

bool Entity::forDeletion() const{
	return _forDeletion;
}

float Entity::getRotation() const{
	return _rotation;
}

void Entity::setRotation(float _rotation) {
	this->_rotation = _rotation;
}

bool Entity::isAlive() const{
	return _alive;
}

void Entity::setAlive(bool _alive) {
	this->_alive = _alive;
}

void Entity::setForDelete(bool _forDelete) {
	this->_forDeletion = _forDelete;
}

bool Entity::isVisible() const{
	return _visible;
}

void Entity::setVisible(bool _visible){
	this->_visible = _visible;
}

// Component ------------------

Component::Component(Entity * const p) : _parent(p){}

bool Component::forDeletion() const{
	return _forDeletion;
}