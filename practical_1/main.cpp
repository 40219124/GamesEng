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

Vector2f ballVelocity;
bool server = false;
bool ai[2] = { false, false };

Font font;
Text text;
int score[2] = { 0,0 };

void reset() {
	// Update score text
	text.setString(score[0] + " : " + score[1]);
	// Keep score text centered 
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
	// Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2.0f, gameHeight / 2.0f);
	paddles[1].setPosition(gameWidth - (10 + paddleSize.x / 2.0f) / 2.0f, gameHeight / 2.0f);
	// Reset ball position
	ball.setPosition(gameWidth / 2.0f, gameHeight / 2.0f);
	// Set ball velocity
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void Load() {
	// Load font-face from res dir
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// Set the character size to 24 pixels
	text.setCharacterSize(24);
	// Set size and origin of paddles 
	for (RectangleShape &p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.0f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3.0f);
	ball.setOrigin(ballRadius / 2.0f, ballRadius / 2.0f);
	reset();
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
	// Set ai players
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {
		ai[0] = !ai[0];
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2)) {
		ai[1] = !ai[1];
	}

	// Handle paddle movement
	for (int i = 0; i < 3; i += 2) {
		float direction = 0.0f;
		if (ai[i / 2]) {
			if (ball.getPosition().y > paddles[i / 2].getPosition().y) {
				direction++;
			}
			if (ball.getPosition().y < paddles[i / 2].getPosition().y) {
				direction--;
			}
		}
		else {
			if (Keyboard::isKeyPressed(controls[i + 0])) {
				direction--;
			}
			if (Keyboard::isKeyPressed(controls[i + 1])) {
				direction++;
			}
		}
		paddles[i / 2].move(0, direction * paddleSpeed * dt);
	}
	ball.move(ballVelocity * dt);
	// Check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) {
		// Bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) {
		// Top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) {
		// Right wall
		reset();
	}
	else if (bx < 0) {
		// Left wall
		reset();
	}
	else if (
		// Ball is inline or behind paddle
		bx < (10 + paddleSize.x) &&
		// and ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		// and ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		// Bounce off left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(5, 0);
	}
	else if (
		// Ball is inline or behind paddle
		bx > gameWidth - (10 + paddleSize.x) &&
		// and ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		// and ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {
		// Bounce off right paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-5, 0);
	}
	for (int i = 0; i < 2; ++i) {
		int py = paddles[i].getPosition().y;
		if (py + (paddleSize.y / 2.0f) > gameHeight) {
			paddles[i].setPosition(paddles[i].getPosition().x, gameHeight - (paddleSize.y / 2.0f));
		}
		else if (py - (paddleSize.y / 2.0f) < 0) {
			paddles[i].setPosition(paddles[i].getPosition().x, paddleSize.y / 2.0f);
		}
	}
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
