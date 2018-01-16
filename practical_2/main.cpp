#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ship.h"

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
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));
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
}

void Render(RenderWindow &window) {
	window.draw(invader);
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