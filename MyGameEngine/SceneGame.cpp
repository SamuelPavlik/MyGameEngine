#include "SceneGame.hpp"
#include "Object.hpp"
#include "WorkingDirectory.hpp"
#include "Input.hpp"
#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"
#include "C_Animation.hpp"
#include "Animation.hpp"
#include "ResourceAllocator.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir, Input& input, ResourceAllocator<sf::Texture>& textureAllocator) :
    workingDir(workingDir),
    input{input},
    textureAllocator{textureAllocator} {}

void SceneGame::OnCreate() {
    player = std::make_shared<Object>();
    player->AddComponent<C_Sprite>(&textureAllocator);
    player->AddComponent<C_KeyboardMovement>(&input);
    auto animation = player->AddComponent<C_Animation>();

    //idle anim definition
    int vikingTextureID = textureAllocator.Add(workingDir.Get() + "viking_sheet.png");
    const int frameWidth = 165;
    const int frameHeight = 145;
    std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>(FacingDirection::Right);
    const float idleAnimFrameSeconds = 0.2f;

    idleAnimation->AddFrame(vikingTextureID, 600, 0,
        frameWidth, frameHeight, idleAnimFrameSeconds);//3
    idleAnimation->AddFrame(vikingTextureID, 800, 0,
        frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 0, 145,
        frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 200, 145,
        frameWidth, frameHeight, idleAnimFrameSeconds);

    animation->AddAnimation(AnimationState::Idle, idleAnimation);

    //adding player to collection
    objects.Add(player);
}

void SceneGame::OnDestroy() {}

void SceneGame::Update(float deltaTime) {
    objects.ProcessRemovals();
    objects.ProcessNewObjects();

    objects.Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime) {
    objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window) {
    objects.Draw(window);
}

