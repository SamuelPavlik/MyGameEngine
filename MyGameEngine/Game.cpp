#include "Game.hpp"
#include "SceneSplashScreen.hpp"
#include "SceneGame.hpp"

#include <iostream>

Game::Game() : window("Game Window") {
    //Input mappings
    input.AddMapping("Left", sf::Keyboard::Left);
    input.AddMapping("Left", sf::Keyboard::A);
    input.AddMapping("Right", sf::Keyboard::Right);
    input.AddMapping("Right", sf::Keyboard::D);
    input.AddMapping("Up", sf::Keyboard::Up);
    input.AddMapping("Up", sf::Keyboard::W);
    input.AddMapping("Down", sf::Keyboard::Down);
    input.AddMapping("Down", sf::Keyboard::S);
    input.AddMapping("Esc", sf::Keyboard::Escape);

    //Initialize scenes
    std::shared_ptr<SceneSplashScreen> splashScreen =
        std::make_shared<SceneSplashScreen>(workingDir, sceneStateMachine, window);

    unsigned int splashScreenID = sceneStateMachine.Add(splashScreen);
    unsigned int gameSceneID = sceneStateMachine.Add(
        std::make_shared<SceneGame>(workingDir, input));

    splashScreen->SetSwitchToScene(gameSceneID);
    sceneStateMachine.SwitchTo(splashScreenID);
    deltaTime = clock.restart().asSeconds();
}

void Game::Update() {
    window.Update();
    sceneStateMachine.Update(deltaTime);
}

void Game::LateUpdate() {
    sceneStateMachine.LateUpdate(deltaTime);
}

void Game::Draw() {
	window.BeginDraw();
    sceneStateMachine.Draw(window);
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
