#pragma once
#include "ecm.h"

class ActorMovementComponent : public Component {
protected:
	bool validMove(const sf::Vector2f&);
	float _speed;

public:
	explicit ActorMovementComponent(Entity *const p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float _speed);

	void move(const sf::Vector2f&);
	void move(float x, float y);

	void Update(const double &dt) override;
	void Render() override {}
};

class PlayerMovementComponent : public ActorMovementComponent {
protected:
	bool validMove(const sf::Vector2f&);

public:
	explicit PlayerMovementComponent(Entity *const p);
	PlayerMovementComponent() = delete;

	void move(const sf::Vector2f&);

	void Update(const double &dt) override;
	void Render() override {}
};

class EnemyAIComponent : public ActorMovementComponent {
public:
	explicit EnemyAIComponent(Entity *const p);
	EnemyAIComponent() = delete;

	bool atWaypoint();

	void Update(const double &dt) override;
	void Render() override {}
protected:
	sf::Vector2f _direction;
	enum state { DEADEND, ROAMING, ROTATING, ROTATED };
	state _state;
private:
	double _noGo = 3.0;
	sf::Vector2f _travel;
};