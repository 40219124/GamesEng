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
	setTextureRect(IntRect(32 * 4, 32, 32, 32));
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
	if (!isExploded()) {
		Ship::Update(dt);

		move(dt * (goRight ? 1.0f : -1.0f) * speed, 0);

		if (goRight && getPosition().x > (gameWidth - 16) || (!goRight && getPosition().x < 16)) {
			goRight = !goRight;
			for (int i = 1; i < ships.size(); ++i) {
				if (!ships[i]->isExploded()) {
					ships[i]->move(0, 24);
				}
			}
		}

		static int random;
		/*static int seed = rand();*/
		//seed = (seed * 23 + 1) % INT16_MAX;
		//srand(seed);
		random = rand() % 100 + 1;

		static float cd = 0.0f;
		if (cd > 0.0f) {
			cd -= dt;
		}

		if (cd <= 0.0f && random <= 1) {
			// Bullet spawn
			Bullet::Fire(getPosition(), true);
			cd += 10.0f;
		}
	}
}

/*    Player    */
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameWidth * 0.5f, gameHeight - 32.0f });
}

void Player::Update(const float &dt) {
	if (!isExploded()) {
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
		static float cd = 0.5f;
		if (cd > 0.0f) {
			cd -= dt;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && cd <= 0.0f) {
			// Bullet spawn
			Bullet::Fire(getPosition(), false);
			cd += 0.5f;
		}
		for (Bullet *const b : bullets) {
			b->Update(dt);
		}
	}
}