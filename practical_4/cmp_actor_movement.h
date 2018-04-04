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
	void Render() override{}
};

class PlayerMovementComponent : public ActorMovementComponent {
public:
	explicit PlayerMovementComponent(Entity *const p);
	PlayerMovementComponent() = delete;

	void Update(const double &dt) override;
	void Render() override {}
};