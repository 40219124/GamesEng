#include "Pacman.h"
#include "ecm.h"
#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include "cmp_actor_movement.h"
#include "LevelSystem.h"

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

void MenuScene::Update(const double &dt) {
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

	ls::loadLevelFile("res/pacman.txt", 25.0f);

	auto pl = make_shared<Entity>();

	auto s = pl->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(12.0f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(12.0f, 12.0f));
	pl->addComponent<PlayerMovementComponent>();

	_player = pl;
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

		ghost->addComponent<EnemyAIComponent>();

		_ents.list.push_back(ghost);
		_ghosts.push_back(ghost);
	}

	respawn();
}

void GameScene::respawn() {
	_player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	_player->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.0f);
	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : _ghosts) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		g->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
	}

}

void GameScene::Update(const double &dt) {
	Scene::Update(dt);
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	for (auto& g : _ghosts) {
		if (length(g->getPosition() - _player->getPosition()) < 25.0f) {
			respawn();
		}
	}
}

void GameScene::Render() {
	ls::Render(Renderer::getWindow());
	Scene::Render();
}