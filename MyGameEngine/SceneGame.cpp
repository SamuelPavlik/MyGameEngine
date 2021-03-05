#include "SceneGame.hpp"
#include "Object.hpp"
#include "WorkingDirectory.hpp"
#include "Input.hpp"
#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir, Input& input, ResourceAllocator<sf::Texture> textureAllocator) :
    workingDir(workingDir),
    input{input},
    textureAllocator{textureAllocator} {}

void SceneGame::OnCreate() {
    player = std::make_shared<Object>();

    auto sprite = player->AddComponent<C_Sprite>(textureAllocator, workingDir.Get() + "attack_0.png");
    //sprite->Load(workingDir.Get() + "attack_0.png");
    auto keyInput = player->AddComponent<C_KeyboardMovement>(&input);
}

void SceneGame::OnDestroy() {}

void SceneGame::Update(float deltaTime) {
    player->Update(deltaTime);
}

void SceneGame::Draw(Window& window) {
    player->Draw(window);
}

void SceneGame::LateUpdate(float deltaTime) {
    player->LateUpdate(deltaTime);
}

