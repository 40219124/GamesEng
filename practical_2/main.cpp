#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

void Reset() {

}

void Load() {
	Reset();
}

void Update(RenderWindow &window) {
	// Calculate delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check events for closing
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	// Quit with esc
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window) {

}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return EXIT_SUCCESS;
}