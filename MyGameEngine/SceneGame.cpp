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
#include "Debug.hpp"

#include <iostream>

SceneGame::SceneGame(const WorkingDirectory& workingDir, Input& input, ResourceAllocator<sf::Texture>& textureAllocator) :
    workingDir(workingDir),
    input{input},
    textureAllocator{textureAllocator},
    mapParser{textureAllocator} {}

void SceneGame::OnCreate() {
    auto player = std::make_shared<Object>();
    
    auto playerSprite = player->AddComponent<C_Sprite>(textureAllocator);
    playerSprite->SetDrawLayer(DrawLayer::Entities);

    player->AddComponent<C_KeyboardMovement>(input);
    
    auto animation = player->AddComponent<C_Animation>();

    // idle anim definition
    auto vikingTextureID = textureAllocator.Add(workingDir.Get() + "viking_sheet.png");
    auto frameWidth = 165;
    auto frameHeight = 145;
    auto idleAnimation = std::make_shared<Animation>(FacingDirection::Right);
    auto idleAnimFrameSeconds = 0.2f;

    idleAnimation->AddFrame(vikingTextureID, 600, 0,
        frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 800, 0,
        frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 0, 145,
        frameWidth, frameHeight, idleAnimFrameSeconds);
    idleAnimation->AddFrame(vikingTextureID, 200, 145,
        frameWidth, frameHeight, idleAnimFrameSeconds);

    // walking anim definition
    auto walkAnimation = std::make_shared<Animation>(FacingDirection::Right);
    auto walkAnimFrameSeconds = 0.15f;

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

    sf::Vector2i mapOffset(-0, 400);
    auto levelTiles = 
        //mapParser.Parse(workingDir.Get() + "MySecondTiledMap.tmx", mapOffset);
        mapParser.Parse(workingDir.Get() + "Test Map 1 - Copy.tmx", mapOffset);

    // add collision component
    player->AddComponent<C_BoxCollider>(sf::FloatRect(0, 0, frameWidth / 2, frameHeight / 1.5f),
        CollisionLayer::Player);

    player->transform->SetPosition(sf::Vector2f(50, 650));

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
    Debug::Draw(window);
}

