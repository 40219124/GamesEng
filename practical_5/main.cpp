#include <SFML/Graphics.hpp>
#include <iostream>
#include "SystemRenderer.h"
#include <ctime>
#include <Box2D\Box2D.h>

using namespace sf;
using namespace std;

b2World* world;
float physics_scale = 30.0f;
float physics_scale_inv = 1.0f / physics_scale;
float gameHeight = 720;
float gameWidth = 1280;

vector<b2Body*> bodies;
vector<RectangleShape*> sprites;

inline const Vector2f bv2_to_sv2(const b2Vec2 & in) {
	return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
	return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}
inline const Vector2f invert_height(const Vector2f& in) {
	return Vector2f(in.x, gameHeight - in.y);
}

b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const Vector2f& position, const Vector2f& size) {
	b2BodyDef bodyDef;
	bodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	bodyDef.position = sv2_to_bv2(position);

	b2Body* body = World.CreateBody(&bodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
	b2FixtureDef FixtureDef;

	FixtureDef.density = dynamic ? 10.0f : 0.0f;
	FixtureDef.friction = dynamic ? 0.8f : 1.0f;
	FixtureDef.restitution = 1.0f;
	FixtureDef.shape = &Shape;

	body->CreateFixture(&FixtureDef);
	return body;
}

b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs) {
	return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void Load() {
	const b2Vec2 gravity(0.0f, -10.0f);
	// Construct a world which holds and simulates physics bodies
	world = new b2World(gravity);
	//Create boxes
	for (int i = 1; i < 11; ++i) {
		// Create SFML shapes for each box
		auto s = new RectangleShape();
		s->setPosition(Vector2f(i * (gameWidth / 12.0f), gameHeight * 0.7f));
		s->setSize(Vector2f(50.0f, 50.0f));
		s->setOrigin(Vector2f(25.0f, 25.0f));
		s->setFillColor(Color::White);
		sprites.push_back(s);

		// Create a dynamic physics body for the box
		auto b = CreatePhysicsBox(*world, true, *s);
		// Give the box a spin
		b->ApplyAngularImpulse(5.0f, true);
		bodies.push_back(b);
	}

	// Wall dimensions
	Vector2f walls[] = {
		// Top
		Vector2f(gameWidth * 0.5f, 5.0f), Vector2f(gameWidth, 10.0f),
		// Bottom
		Vector2f(gameWidth* 0.5f, gameHeight - 5.0f), Vector2f(gameWidth, 10.0f),
		// Left
		Vector2f(2.0f, gameHeight * 0.5f), Vector2f(10.0f, gameHeight),
		// Right
		Vector2f(gameWidth - 5.0f, gameHeight * 0.5f), Vector2f(10.0f, gameHeight)
	};

	for (int i = 0; i < 7; i += 2) {
		// Create sfml shapes for each wall
		auto s = new RectangleShape();
		s->setPosition(walls[i]);
		s->setSize(walls[i + 1]);
		s->setOrigin(walls[i + 1] / 2.0f);
		s->setFillColor(Color::White);
		sprites.push_back(s);

		auto b = CreatePhysicsBox(*world, false, *s);
		bodies.push_back(b);
	}
}

void Update(RenderWindow &window) {
	static Clock clock;
	float dt = clock.restart().asSeconds();

	world->Step(dt, 2, 2);

	for (int i = 0; i < bodies.size(); ++i) {
		// Sync sprites to physics position
		sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
		// Sync sprites to physics rotation
		sprites[i]->setRotation((180.0f / b2_pi) * bodies[i]->GetAngle());
	}

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
	for (RectangleShape* rs : sprites) {
		Renderer::queue(rs);
	}
	Renderer::Render();
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Physics");
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