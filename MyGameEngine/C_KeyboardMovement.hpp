#ifndef C_KeyboardMovement_hpp
#define C_KeyboardMovement_hpp

#include "Component.hpp"
#include <memory>

class Input;
class C_Animation;

class C_KeyboardMovement : public Component {
public:
    C_KeyboardMovement(Object* owner, Input* input);

    void Awake() override;

    void SetInput(Input* input);

    void SetMovementSpeed(int moveSpeed);

    void Update(float deltaTime) override;

private:
    int moveSpeed;
    Input* input;
    std::shared_ptr<C_Animation> animation;
};

#endif /* C_KeyboardMovement_hpp */