#pragma once
#include "Entity.h"

class Ghost : public Entity {
private:
	float _speed;
	sf::Vector2f _travel = sf::Vector2f(0.0f, 0.0f);
	float _noGo = 5.0f;

public:
	void Update(const float dt) override;
	Ghost();
	void Render() override;
};