#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer {
	void initialise(sf::RenderWindow &r);
	sf::RenderWindow &getWindow();

	void Shutdown();
	void Update(const double &dt);
	void queue(const sf::Drawable *s);
	void Render();
};