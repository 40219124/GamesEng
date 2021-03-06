#include "Bullet.h"
#include "Game.h"
#include "Ship.h"
using namespace sf;
using namespace std;

Bullet Bullet::bullets[256];

Bullet::Bullet() {
	setPosition(Vector2f(0.0f, 0.0f));
	_mode = true;
	setTexture(spritesheet);
	if (_mode) {
		setTextureRect(IntRect(32, 32, 32, 32));
	}
	else {
		setTextureRect(IntRect(64, 32, 32, 32));
	}
}

void Bullet::Update(const float &dt) {
	for (Bullet &b : bullets) {
		b._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow &window) {
	for (const Bullet &b : bullets) {
		if (b._active) {
			window.draw(b);
		}
	}
}

void Bullet::_Update(const float &dt) {
	if (_active) {
		if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
			_active = false;
		}
		else {
			move(0.0f, dt * 200.0f * (_mode ? 1.0f : -1.0f));
			const FloatRect boundingBox = getGlobalBounds();

			for (Ship *s : ships) {
				if (!_mode && s == ships[0]) {
					continue;
				}
				if (_mode && s != ships[0]) {
					continue;
				}
				if (!s->isExploded() && s->getGlobalBounds().intersects(boundingBox)) {
					s->Explode();
					setPosition(-111, -111);
					_active = false;
					return;
				}
			}
		}
	}
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode) {
	for (Bullet &b : bullets) {
		if (!b._active) {
			b._active = true;
			b.setPosition(pos);
			b._mode = mode;
			b.setTexture(spritesheet);
			if (b._mode) {
				b.setTextureRect(IntRect(32 + 12, 32 + 9 + 10, 8, -10));
			}
			else {
				b.setTextureRect(IntRect(64 + 12, 32 + 9, 8, 10));
			}
			break;
		}
	}
}