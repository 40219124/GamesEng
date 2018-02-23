#include "Player.h"
using namespace sf;
using namespace std;

void Player::Update(const float dt) {
	// player update things
	Entity::Update(dt);
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
	dir *= dt * _speed;
	move(dir);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Player::Render(sf::RenderWindow &window)const {
	window.draw(*_shape);
}