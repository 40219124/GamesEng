#include "cmp_actor_movement.h"
#include <LevelSystem.h>

using namespace sf;
using namespace std;

/// Actor Movement Component /// 

void ActorMovementComponent::Update(const double &dt) {}

ActorMovementComponent::ActorMovementComponent(Entity * const p)
	: _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
	// return true;
	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
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

PlayerMovementComponent::PlayerMovementComponent(Entity *const p) : ActorMovementComponent(p) {}

bool PlayerMovementComponent::validMove(const sf::Vector2f &pos)
{
	return (LevelSystem::getTileAt(pos) != LevelSystem::ENEMY);
}

void PlayerMovementComponent::move(const sf::Vector2f& p) {
	if (validMove(_parent->getPosition() + p)) {
		ActorMovementComponent::move(p);
	}
}

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
	if (dir != Vector2f(0, 0)) {
		int x = 5;
	}
	move(dir);
}

/// Enemy Movement Component ///

EnemyAIComponent::EnemyAIComponent(Entity *const p) : ActorMovementComponent(p) {
	_direction = { 0,1 };
	_state = ROAMING;
}

bool EnemyAIComponent::atWaypoint() {
	Vector2f pos = _parent->getPosition();
	if (ls::getTileAt(pos) == ls::WAYPOINT) {
		Vector2f tilePos = ls::getTilePosNear(pos);
		Vector2f distance = tilePos - pos;
		if (distance == Vector2f(0, 0) || length2(distance) <= 157) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

void EnemyAIComponent::Update(const double &dt) {
	/*ActorMovementComponent::Update(dt);

	_noGo -= dt;
	if (_noGo <= 0.0f) {
		Vector2f dir = Vector2f(0.0f, 0.0f);
		dir.x = rand() % 5 - 2;
		dir.y = rand() % 5 - 2;
		_travel = normalize(dir);

		_noGo = (rand() % 5 + 1) / 3.0;
	}
	move(_travel * (float)dt * _speed);*/

	const auto mva = (float)(dt * _speed);
	const Vector2f travel = _direction * mva;
	const Vector2f pos = _parent->getPosition();
	const Vector2f newpos = pos + travel;
	const Vector2i baddir = -1 * Vector2i(_direction);
	Vector2i newdir = directions[(rand() % 4)];

	switch (_state) {
	case ROAMING:
		if (!validMove(newpos) || atWaypoint()) {
			// start rotate
			_state = ROTATING;
		}
		else {
			// keep moving
			move(travel);
		}
		break;
	case ROTATING:
	{
		vector<Vector2i> options;
		for (Vector2i pair : directions) {
			if (Vector2f(pair) != _direction * -1.0f) {
				options.push_back(pair);
			}
		}
		bool picked = false;
		while (options.size() != 0/*not done*/) {
			// pick new direction
			int ran = rand() % options.size();
			newdir = options[ran];
			options.erase(options.begin() + ran);
			if (validMove(_parent->getPosition() + Vector2f(newdir) * 26.0f)) {
				picked = true;
				break;
			}
		}
		if (picked) {
			_direction = Vector2f(newdir);
		}
		else {
			_direction = -_direction;
		}
		_state = ROTATED;
		break;
	}
	case ROTATED:
		// have we left the waypoint?
		if (!atWaypoint()) {
			_state = ROAMING;
		}
		move(_direction * mva);
		break;
	}
	ActorMovementComponent::Update(dt);
}