#ifndef C_KeyboardMovement_hpp
#define C_KeyboardMovement_hpp

#include "Component.hpp"

class Input;

class C_KeyboardMovement : public Component {
public:
    C_KeyboardMovement(Object* owner);

    void SetInput(Input* input);
    void SetMovementSpeed(int moveSpeed);

    void Update(float deltaTime) override;

private:
    int moveSpeed;
    Input* input;
};

#endif /* C_KeyboardMovement_hpp */