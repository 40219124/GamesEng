#include "Pacman.h"
#include "Player.h"
#include "Ghost.h"
#include "SystemRenderer.h"

using namespace std;
using namespace sf;

void MenuScene::Load() {
	Font* font = new Font();
	font->loadFromFile("res/fonts/RobotoMono-Regular.ttf");

	text = Text();
	text.setFont(*font);
	text.setString("Almost pacman!");
	text.setColor(Color::White);
	text.setPosition(1920.0f / 2.0f - text.getGlobalBounds().width / 2.0f, 1080.0f / 2.0f - text.getGlobalBounds().height / 2.0f);
}

void MenuScene::Update(const double dt) {
	Scene::Update(dt);
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
}

void MenuScene::Render() {
	Scene::Render();
	Renderer::queue(&text);
}

void GameScene::Load() {
	gameScene->getEnts().push_back(shared_ptr<Entity>(new Player()));
	for (int i = 0; i < 4; ++i) {
		gameScene->getEnts().push_back(shared_ptr<Entity>(new Ghost()));
		gameScene->getEnts()[gameScene->getEnts().size() - 1]->setPosition(Vector2f(1000, 500));
	}
}

void GameScene::Update(const double dt) {
	Scene::Update(dt);
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
}

void GameScene::Render() {
	Scene::Render();
}