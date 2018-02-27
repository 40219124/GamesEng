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
	player.Render(window);
	ls::Render(window);
}

int main() {
	RenderWindow window(VideoMode(800, 600), "Tile maze");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}