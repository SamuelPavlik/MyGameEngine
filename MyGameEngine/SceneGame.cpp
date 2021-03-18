#include "SceneGame.hpp"
#include "Object.hpp"
#include "WorkingDirectory.hpp"
#include "Input.hpp"
#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"
#include "C_Animation.hpp"
#include "C_BoxCollider.hpp"
#include "Animation.hpp"
#include "ResourceAllocator.hpp"

#include <iostream>

SceneGame::SceneGame(WorkingDirectory& workingDir, Input& input, ResourceAllocator<sf::Texture>& textureAllocator) :
    workingDir(workingDir),
    input{input},
    textureAllocator{textureAllocator},
    mapParser{textureAllocator} {}

void SceneGame::OnCreate() {
    player = std::make_shared<Object>();
    player->AddComponent<C_Sprite>(&textureAllocator);
    player->AddComponent<C_KeyboardMovement>(&input);
    auto animation = player->AddComponent<C_Animation>();

    // idle anim definition
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

    // walking anim definition
    std::shared_ptr<Animation> walkAnimation =
        std::make_shared<Animation>(FacingDirection::Right);
    const float walkAnimFrameSeconds = 0.15f;

    walkAnimation->AddFrame(vikingTextureID, 600, 290,
        frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 800, 290,
        frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 0, 435,
        frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 200, 435,
        frameWidth, frameHeight, walkAnimFrameSeconds);
    walkAnimation->AddFrame(vikingTextureID, 400, 435,
        frameWidth, frameHeight, walkAnimFrameSeconds);

    // add animations to our Viking
    animation->AddAnimation(AnimationState::Walk, walkAnimation);
    animation->AddAnimation(AnimationState::Idle, idleAnimation);

    sf::Vector2i mapOffset(-192, -360);
    std::vector<std::shared_ptr<Object>> levelTiles = 
        //mapParser.Parse(workingDir.Get() + "MySecondTiledMap.tmx", mapOffset);
        mapParser.Parse(workingDir.Get() + "Test Map 1 - Copy.tmx", mapOffset);

    // add collision component
    player->AddComponent<C_BoxCollider>(sf::FloatRect(0, 0, frameWidth, frameHeight),
        CollisionLayer::Player);

    objects.Add(levelTiles);
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

