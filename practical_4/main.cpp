#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"
#include "Entity.h"
#include "Player.h"
#include "Ghost.h"

using namespace sf;
using namespace std;

EntityManager em;
vector<Entity*> ents;

void Reset(){}

void Load(){
	em.list.push_back(shared_ptr<Entity>(new Player()));
	for (int i = 0; i < 4; ++i) {
		em.list.push_back(shared_ptr<Entity>(new Ghost()));
		em.list[em.list.size() - 1]->setPosition(Vector2f(1000, 500));
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
	em.Update(dt);
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window){
	em.Render(window);
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