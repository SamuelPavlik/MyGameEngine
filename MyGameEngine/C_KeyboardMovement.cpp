#include "C_KeyboardMovement.hpp"
#include "Object.hpp"
#include "Input.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object* owner)
    : Component(owner), moveSpeed(100) {
}

void C_KeyboardMovement::SetInput(Input* input) {
    this->input = input;
}

void C_KeyboardMovement::SetMovementSpeed(int moveSpeed) {
    this->moveSpeed = moveSpeed;
}

void C_KeyboardMovement::Update(float deltaTime) {
    if (input == nullptr) {
        return;
    }

    int xMove = 0;
    if (input->IsKeyPressed("Left")) {
        xMove = -moveSpeed;
    }
    else if (input->IsKeyPressed("Right")) {
        xMove = moveSpeed;
    }

    int yMove = 0;
    if (input->IsKeyPressed("Up")) {
        yMove = -moveSpeed;
    }
    else if (input->IsKeyPressed("Down")) {
        yMove = moveSpeed;
    }

    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;

    owner->transform->AddPosition(xFrameMove, yFrameMove);
}