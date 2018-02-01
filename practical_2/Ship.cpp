#include "Ship.h"
#include "Game.h"

using namespace sf;
using namespace std;

/*    Ship    */
Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float &dt) {}

Ship::~Ship() = default;

/*  Invader  */

bool Invader::goRight = true;
float Invader::speed = 64.0f;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt * (goRight ? 1.0f : -1.0f) * speed, 0);

	if (goRight && getPosition().x > (gameWidth - 16) || (!goRight && getPosition().x < 16)) {
		goRight = !goRight;
		for (int i = 1; i < ships.size(); ++i) {
			ships[i]->move(0, 24);
		}
	}
}

/*    Player    */
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * 0.5f, gameHeight - 32.0f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);
	float speed = 128.0f;
	// Move left
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		float distance = -speed * dt;
		if ((distance + this->getPosition().x) < 16) {
			distance = -(this->getPosition().x - 16);
		}
		move({ distance, 0.0f });
	}
	// Move right
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		float distance = speed * dt;
		if ((distance + this->getPosition().x) > (gameWidth - 16)) {
			distance = ((gameWidth - 16) - this->getPosition().x);
		}
		move({ distance, 0.0f });
	}
}