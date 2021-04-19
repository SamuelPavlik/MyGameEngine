#include "C_KeyboardMovement.hpp"
#include "Object.hpp"
#include "Input.hpp"
#include "C_Animation.hpp"
#include "Animation.hpp"
#include "Constants.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object& owner, Input& input)
    : Component(owner), input(input), moveSpeed(MOVE_SPEED) {
}

void C_KeyboardMovement::Awake() {
    animation = owner.GetComponent<C_Animation>();
}

void C_KeyboardMovement::Update(float deltaTime) {
    auto xMove = 0;
    if (input.IsKeyPressed("Left")) {
        xMove = -moveSpeed;
        animation->SetAnimationDirection(FacingDirection::Left);
    }
    else if (input.IsKeyPressed("Right")) {
        xMove = moveSpeed;
        animation->SetAnimationDirection(FacingDirection::Right);
    }

    auto yMove = 0;
    if (input.IsKeyPressed("Up")) {
        yMove = -moveSpeed;
    }
    else if (input.IsKeyPressed("Down")) {
        yMove = moveSpeed;
    }

    if (xMove == 0 && yMove == 0) {
        animation->SetAnimationState(AnimationState::Idle);
    }
    else {
        animation->SetAnimationState(AnimationState::Walk);
    }

    auto xFrameMove = xMove * deltaTime;
    auto yFrameMove = yMove * deltaTime;

    owner.transform->AddPosition(xFrameMove, yFrameMove);
}

void C_KeyboardMovement::SetMovementSpeed(int moveSpeed) {
    this->moveSpeed = moveSpeed;
}