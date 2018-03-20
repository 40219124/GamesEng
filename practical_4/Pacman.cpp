#include "Pacman.h"
#include "Player.h"
#include "Ghost.h"
#include "SystemRenderer.h"

using namespace std;
using namespace sf;

void MenuScene::Load() {

}

void MenuScene::Update(const double dt) {
	Scene::Update(dt);
}

void MenuScene::Render() {
	Scene::Render();
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
}

void GameScene::Render() {
	Scene::Render();
}