#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"
#include "Entity.h"
#include "Scene.h"
#include "Pacman.h"
#include "SystemRenderer.h"
#include <ctime>

using namespace sf;
using namespace std;

shared_ptr<Scene> activeScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> gameScene;
vector<Entity*> ents;

void Reset(){}

void Load(){
	srand(static_cast<unsigned int>(time(0)));
	// Load scene-local assets
	menuScene.reset(new MenuScene());
	gameScene.reset(new GameScene());
	menuScene->Load();
	gameScene->Load();
	// Start on menu
	activeScene = menuScene;
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
	activeScene->Update(dt);
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window){
	activeScene->Render();
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