#include "Game.hpp"
#include <iostream>

Game::Game() : window("Game Window") {
	deltaTime = clock.restart().asSeconds();

	vikingTexture.loadFromFile(workingDir.Get() + "attack_0.png");
	vikingSprite.setTexture(vikingTexture);

    input.AddMapping("Left", sf::Keyboard::Left);
    input.AddMapping("Left", sf::Keyboard::A);
    input.AddMapping("Right", sf::Keyboard::Right);
    input.AddMapping("Right", sf::Keyboard::D);
    input.AddMapping("Up", sf::Keyboard::Up);
    input.AddMapping("Up", sf::Keyboard::W);
    input.AddMapping("Down", sf::Keyboard::Down);
    input.AddMapping("Down", sf::Keyboard::S);
    input.AddMapping("Esc", sf::Keyboard::Escape);
}

void Game::Update() {
	const auto& spritePos = vikingSprite.getPosition();
	const int moveSpeed = 100;

    int xMove = 0;
    if (input.IsKeyPressed("Left")) {
        xMove = -moveSpeed;
    }
    else if (input.IsKeyPressed("Right")) {
        xMove = moveSpeed;
    }

    int yMove = 0;
    if (input.IsKeyPressed("Up")) {
        yMove = -moveSpeed;
    }
    else if (input.IsKeyPressed("Down")) {
        yMove = moveSpeed;
    }

    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;

    vikingSprite.setPosition(spritePos.x + xFrameMove, spritePos.y + yFrameMove);
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

void Game::CaptureInput() {
	input.Update();
}
