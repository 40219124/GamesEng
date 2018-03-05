#include "Ghost.h"
#include "maths.h"
using namespace sf;
using namespace std;

void Ghost::Update(const float dt) {
	Entity::Update(dt);
	
	_noGo -= dt;
	if (_noGo <= 0.0f) {
		Vector2f dir = Vector2f(0.0f, 0.0f);
		dir.x = rand() % 5 - 2;
		dir.y = rand() % 5 - 2;
		dir = normalize(dir);
		_travel = dir;

		_noGo = rand() % 5 + 1;
	}
	move(_travel * dt * _speed);
}

Ghost::Ghost() : _speed(180.0f), Entity(make_unique<CircleShape>(20.0f)) {
	_shape->setFillColor(Color::Red);
	_shape->setOrigin(Vector2f(25.0f, 25.0f));
}

void Ghost::Render(sf::RenderWindow &window)const {
	window.draw(*_shape);
}