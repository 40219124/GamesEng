#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"
#include "Game.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;

vector<Ship *> ships;

void Reset() {

}

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << endl;
	}
	/*Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100,100 });
	ships.push_back(inv);*/
	Player* player = new Player();
	ships.push_back(player);

	for (int r = 0; r < invaders_rows; ++r) {
		IntRect rect = IntRect(32 * (r < 6 ? r : 0), 0, 32, 32);
		for (int c = 0; c < invaders_columns; ++c) {
			Vector2f position = { 21 + 40.0f * c, 21 + 40.0f * r };
			Invader* inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}

	Reset();
}

void Update(RenderWindow &window) {
	// Calculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check events for closing
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	// Quit with esc
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	for (Ship* s : ships) {
		s->Update(dt);
	}
}

void Render(RenderWindow &window) {
	window.draw(invader);
	for (const Ship* s : ships) {
		window.draw(*s);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}