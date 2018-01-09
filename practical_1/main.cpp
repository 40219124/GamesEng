#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A,
	Keyboard::Z,
	Keyboard::Up,
	Keyboard::Down
};
const Vector2f paddleSize(25.0f, 100.0f);
const float ballRadius = 10.0f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.0f;

CircleShape ball;
RectangleShape paddles[2];

void Load() {
	// Set size and origin of paddles 
	for (RectangleShape &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.0f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3.0f);
	ball.setOrigin(ballRadius / 2.0f, ballRadius / 2.0f);
	// Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2.0f, gameHeight / 2.0f);
	paddles[1].setPosition(gameWidth - (10 + paddleSize.x) / 2.0f, gameHeight / 2.0f);
	// Reset ball position
	ball.setPosition(0.0f, 0.0f);
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via esc key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Handle paddle movement
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	paddles[0].move(0, direction * paddleSpeed * dt);
}

void Render(RenderWindow &window) {
	// Draw everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
	{

	}
}


//#include <SFML/Graphics.hpp>
//
//int main(){
//	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//	sf::CircleShape shape(100.0f);
//	shape.setFillColor(sf::Color::Green);
//	
//	while (window.isOpen()){
//		sf::Event event;
//		while (window.pollEvent(event)){
//			if (event.type == sf::Event::Closed){
//				window.close();
//			}
//		}
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//	return 0;
//}
