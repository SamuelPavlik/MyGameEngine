#include "SceneGame.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir, Input& input) : 
    workingDir(workingDir),
    input{input} {}

void SceneGame::OnCreate() {
    vikingTexture.loadFromFile(workingDir.Get() + "attack_0.png");
    vikingSprite.setTexture(vikingTexture);
}

void SceneGame::OnDestroy() {}

void SceneGame::Update(float deltaTime) {
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

void SceneGame::Draw(Window& window) {
    window.Draw(vikingSprite);
}

