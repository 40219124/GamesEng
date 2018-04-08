#pragma once
#include "Scene.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();
	std::shared_ptr<Entity> _player;
	std::vector<std::shared_ptr<Entity>> _ghosts;

public:
	GameScene() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
};