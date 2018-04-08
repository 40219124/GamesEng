#include "LevelSystem.h"
#include "maths.h"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset(Vector2f(0.0f, 30.0f));

float LevelSystem::_tileSize(100.0f);
vector<unique_ptr<RectangleShape>> LevelSystem::_sprites;

map<LevelSystem::TILE, Color> LevelSystem::_colors{
	{WALL, Color::White}, {END, Color::Red} };

Color LevelSystem::getColor(LevelSystem::TILE t) {
	auto it = _colors.find(t);
	if (it == _colors.end()) {
		_colors[t] = Color::Transparent;
	}
	return _colors[t];
}

void LevelSystem::setColor(LevelSystem::TILE t, Color c) {
	// set colour
	_colors.insert_or_assign(t, c);
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(TILE t)
{
	vector<Vector2ul> out;
	for (int i = 0; i < _width * _height; ++i) {
		if (_tiles[i] == t) {
			out.push_back(Vector2ul(i%_width, i / _width));
		}
	}
	return out;
}

void LevelSystem::loadLevelFile(const string& path, float tileSize) {
	_tileSize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	// Load in file to buffer
	ifstream f(path);
	if (f.good()) {
		f.seekg(0, ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	}
	else {
		throw string("Couldn't open level file: ") + path;
	}

	vector<TILE> temp_tiles;
	for (int i = 0; i < buffer.size(); ++i) {
		const char c = buffer[i];
		switch (c) {
		case 'w':
			temp_tiles.push_back(WALL);
			break;
		case 's':
			temp_tiles.push_back(START);
			break;
		case 'e':
			temp_tiles.push_back(END);
			break;
		case ' ':
			temp_tiles.push_back(EMPTY);
			break;
		case '+':
			temp_tiles.push_back(WAYPOINT);
			break;
		case 'n':
			temp_tiles.push_back(ENEMY);
			break;
		case '\n':			// end of line
			if (w == 0) {	// if we haven't written width yet
				w = i;		// set width
			}
			h++;			// increment height
			break;
		default:
			cout << c << endl; // Don't know what this tile type is
		}
	}
	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level file") + path;
	}
	_tiles = make_unique<TILE[]>(w * h);
	_width = w;		// Set static class vars
	_height = h;
	copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << " Loaded. " << w << "x" << h << endl;
	buildSprites();
}

void LevelSystem::buildSprites() {
	_sprites.clear();
	float shift = _tileSize / 2.0f;
	for (size_t y = 0; y < ls::_height; ++y) {
		for (size_t x = 0; x < ls::_width; ++x) {
			auto s = make_unique<RectangleShape>();
			Vector2f pos = getTilePosition({ x, y });
			s->setOrigin(Vector2f(shift, shift));
			s->setPosition(Vector2f(pos.x, pos.y));
			s->setSize(Vector2f(_tileSize, _tileSize));
			s->setFillColor(getColor(getTile({ x, y })));
			_sprites.push_back(move(s));
		}
	}
}

Vector2f LevelSystem::getTilePosition(Vector2ul p) {
	return (Vector2f(p.x + 0.5f, p.y + 0.5f) * _tileSize) + _offset;
	/*auto x = _sprites[p.x + p.y * _width].get();
	return x->getPosition();*/
	//return (Vector2f(p.x, p.y) * _tileSize);
}

LevelSystem::TILE LevelSystem::getTile(Vector2ul p) {
	if (p.x > _width || p.y > _height) {
		throw string("Tile out of range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
	}
	return _tiles[(p.y * _width) + p.x];
}

LevelSystem::TILE LevelSystem::getTileAt(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		throw string("Tile out of range.");
	}
	return getTile(Vector2ul(a / (_tileSize)));
}

sf::Vector2f LevelSystem::getTilePosNear(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		throw string("Tile out of range.");
	}
	return getTilePosition(Vector2ul(a / (_tileSize)));
}

void LevelSystem::Render(RenderWindow &window) {
	for (size_t i = 0; i < _width * _height; ++i) {
		window.draw(*_sprites[i]);
	}
}