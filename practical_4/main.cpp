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
}

void Render(RenderWindow &window){
}

int main() {
	RenderWindow window(VideoMode(1920, 1080), "PacMan");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}