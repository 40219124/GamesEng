#include "Pacman.h"
#include "ecm.h"
#include "cmp_sprite.h"
#include "SystemRenderer.h"

#define GHOSTS_COUNT 4

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

	auto pl = make_shared<Entity>();

	auto s = pl->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(12.0f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(12.0f, 12.0f));

	_ents.list.push_back(pl);

	const Color ghost_cols[]{ {208, 62, 250},	// red Blinky
							{219, 133, 28},		// orange Clyde
							{70, 191, 238},		// cyan Inky
							{234, 130, 229} };	// pink Pinky

	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<CircleShape>(12.0f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.0f, 12.0f));

		_ents.list.push_back(ghost);
	}

	/*gameScene->getEnts().push_back(shared_ptr<Entity>(new Player()));
	for (int i = 0; i < 4; ++i) {
		gameScene->getEnts().push_back(shared_ptr<Entity>(new Ghost()));
		gameScene->getEnts()[gameScene->getEnts().size() - 1]->setPosition(Vector2f(1000, 500));
	}*/
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