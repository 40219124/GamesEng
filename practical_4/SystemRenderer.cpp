#include "SystemRenderer.h"
#include <queue>

using namespace std;
using namespace sf;

static queue<const Drawable *> sprites;
static RenderWindow *rw;

void Renderer::initialise(sf::RenderWindow &r) {
	rw = &r;
}

sf::RenderWindow &Renderer::getWindow() { return *rw; }

void Renderer::Shutdown() {
	while (!sprites.empty()) {
		sprites.pop();
	}
}

void Renderer::Update(const double &dt) {}

void Renderer::Render() {
	if (rw == nullptr) {
		throw("No render window set!");
	}
	while (!sprites.empty()) {
		rw->draw(*sprites.front());
		sprites.pop();
	}
}