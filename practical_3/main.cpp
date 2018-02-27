#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"
#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

Player player;

void Reset(){}

void Load(){
	float tileSize = 200.0f;
	ls::loadLevelFile("res/maze_02.txt", tileSize);
	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x,y });
			if (ls::getTile({ x,y }) == ls::START) {
				Vector2f start = ls::getTilePosition({ x,y });
				start.x += tileSize / 2.0f;
				start.y += tileSize / 2.0f;
				player.setPosition(start);
			}
		}
		cout << endl;
	}
}

void Update(RenderWindow &window){
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

	player.Update(dt);
}

void Render(RenderWindow &window){
	ls::Render(window);
	player.Render(window);
}

int main() {
	RenderWindow window(VideoMode(1600, 1000), "Tile maze");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}