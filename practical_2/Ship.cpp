#include "Ship.h"
#include "Game.h"
#include "Bullet.h"

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

void Ship::Explode() {
	_exploded = true;
}

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
	setPosition({ gameWidth * 0.5f, gameHeight - 32.0f });
}

void Player::Update(const float &dt) {
	static vector<Bullet*> bullets;
	Ship::Update(dt);
	float speed = 248.0f;
	// Move left
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		float distance = -speed * dt;
		int spriteWidth = 0;
		if ((distance + this->getPosition().x) < spriteWidth) {
			distance = -(this->getPosition().x - spriteWidth);
		}
		move({ distance, 0.0f });
	}
	// Move right
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		float distance = speed * dt;
		int spriteWidth = 32;
		if ((distance + this->getPosition().x) > (gameWidth - spriteWidth)) {
			distance = ((gameWidth - spriteWidth) - this->getPosition().x);
		}
		move({ distance, 0.0f });
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		// Bullet spawn
		bullets.push_back(new Bullet(getPosition(), false));
	}
	for (Bullet *const b : bullets) {
		b->Update(dt);
	}
}