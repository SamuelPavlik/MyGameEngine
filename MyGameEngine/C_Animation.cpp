#include "C_Animation.hpp"
#include "Object.hpp"
#include "C_Sprite.hpp"

C_Animation::C_Animation(Object* owner) : Component(owner),
currentAnimation(AnimationState::None, nullptr) {}

void C_Animation::Awake() {
    sprite = owner->GetComponent<C_Sprite>();
}

void C_Animation::Update(float deltaTime) {
    if (currentAnimation.first == AnimationState::None ||
        !currentAnimation.second->UpdateFrame(deltaTime)) {
        return;
    }

    const auto* data = currentAnimation.second->GetCurrentFrame();
    if (data && sprite) {
        sprite->Load(data->id);
        sprite->SetTextureRect(data->x, data->y, data->width, data->height);
    }
}

void C_Animation::AddAnimation(AnimationState state, const std::shared_ptr<Animation>& animation) {
    animations.insert(std::make_pair(state, animation));

    if (currentAnimation.first == AnimationState::None) {
        SetAnimationState(state);
    }
}

void C_Animation::SetAnimationState(AnimationState state) {
    if (currentAnimation.first == state) {
        return;
    }

    auto animation = animations.find(state);
    if (animation != animations.end()) {
        currentAnimation.first = animation->first;
        currentAnimation.second = animation->second;
        currentAnimation.second->Reset();
    }
}

const AnimationState& C_Animation::GetAnimationState() const {
    return currentAnimation.first;
}

void C_Animation::SetAnimationDirection(FacingDirection dir) {
    if (currentAnimation.first != AnimationState::None) {
        currentAnimation.second->SetDirection(dir);
    }
}