#include "cmp_actor_movement.h"
#include <LevelSystem.h>
#include <SFML/Graphics.hpp>
#include "maths.h"

#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

using namespace sf;
using namespace std;

/// Actor Movement Component /// 

void ActorMovementComponent::Update(const double &dt) {}

ActorMovementComponent::ActorMovementComponent(Entity * const p)
	: _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	return true;
	//return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}

/// Player Movement Component ///

PlayerMovementComponent::PlayerMovementComponent(Entity *const p) : ActorMovementComponent(p){}

void PlayerMovementComponent::Update(const double &dt) {
	// player update things
	ActorMovementComponent::Update(dt);
	Vector2f dir = Vector2f(0.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		dir += Vector2f(-1.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		dir += Vector2f(0.0f, -1.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		dir += Vector2f(0.0f, 1.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dir += Vector2f(1.0f, 0.0f);
	}
	dir = normalize(dir) * (float)dt * _speed;
	move(dir);
}