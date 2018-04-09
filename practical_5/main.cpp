#include <SFML/Graphics.hpp>
#include <iostream>
#include "SystemRenderer.h"
#include <ctime>
#include <Box2D\Box2D.h>

using namespace sf;
using namespace std;

b2World* world;
float physics_scale = 1.0f / 30.0f;
float physics_scale_inv = 1.0f / physics_scale;

inline const Vector2f bv2_to_sv2(const b2Vec2 & in) {
	return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
	return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}

void Reset() {}

void Load() {
	const b2Vec2 gravity(0.0f, -10.0f);
	// Construct a world which holds and simulates physics bodies
	world = new b2World(gravity);
}

void Update(RenderWindow &window) {
	static Clock clock;
	float dt = clock.restart().asSeconds();
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window) {
	Renderer::Render();
}

int main() {
	RenderWindow window(VideoMode(1920, 1080), "PacMan");
	Renderer::initialise(window);
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}