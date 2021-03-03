#include "Game.hpp"

Game::Game() : window("Game Window") {
	deltaTime = clock.restart().asSeconds();

	vikingTexture.loadFromFile(workingDir.Get() + "attack_0.png");
	vikingSprite.setTexture(vikingTexture);
}

void Game::Update() {
	const auto& spritePos = vikingSprite.getPosition();
	const int pixelsToMovePerSec = 50;
	const float frameMovement = pixelsToMovePerSec * deltaTime;
	vikingSprite.setPosition(spritePos.x + frameMovement, spritePos.y);
}

void Game::LateUpdate() {}

void Game::Draw() {
	window.BeginDraw();

	window.Draw(vikingSprite);

	window.EndDraw();
}

bool Game::IsRunning() const {
	return window.IsOpen();
}

void Game::CalculateDeltaTime() {
	deltaTime = clock.restart().asSeconds();
}
