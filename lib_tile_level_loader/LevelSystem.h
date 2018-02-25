#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem

class LevelSystem {
public:
	enum TILE { EMPTY, START, END, WALL, ENEMY, WAYPOINT };

	static void loadLevelFile(const std::string&, float tileSize = 100.0f);
	static void Render(sf::RenderWindow &window);
	static sf::Color getColor(TILE t);
	static void setColor(TILE t, sf::Color c);
	// Get tile at grid coordinate
	static TILE getTile(sf::Vector2ul);
	// Get screenspace coordinate of tile
	static sf::Vector2f getTilePosition(sf::Vector2ul);
	// Get the tile at screenspace pos
	static TILE getTileAt(sf::Vector2f);

protected:
	static std::unique_ptr < TILE[]> _tiles;  //Internal array of tiles
	static size_t _width; // How many tiles wide is level
	static size_t _height;  // How many tiles high is level
	static sf::Vector2f _offset; // Screenspace offset of level, when rendered
	static float _tileSize; // Screenspace size of each tile, when rendered
	static std::map<TILE, sf::Color> _colors; // Color to render each tile type

	// Array of sfml sprites of each tile
	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
	// Generate the _sprites array
	static void buildSprites();

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};