#include "LevelSystem.h"
#include <fstream>

using namespace std;
using namespace sf;

unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset(0.0f, 30.0f);

float LevelSystem::_tileSyize(100.0f);
vector<unique_ptr<RectangleShape>> Level_System::_sprites;

map<LevelSystem::TILE, Color> LevelSystem::_colours{
auto it = _colours.find(t);
if (it == _colour.end()) {
	_colours[t] = colour::Transparent;
}
return _colours[t];
}

void LevelSystem::setColor(LevelSystem::TILE t, Color c) {
	// set colour
}