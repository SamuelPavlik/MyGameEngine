#include "C_Transform.hpp"

C_Transform::C_Transform(Object& owner) : 
    Component(owner), 
    position(0.f, 0.f), 
    isStaticTransform(false) {}

C_Transform::C_Transform(Object& owner, bool isStaticTransform) : 
    Component(owner), 
    position(0.f, 0.f), 
    isStaticTransform(isStaticTransform) {}

void C_Transform::SetPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void C_Transform::SetPosition(const sf::Vector2f& pos) {
    position = pos;
}

void C_Transform::SetStatic(bool isStatic) {
    isStaticTransform = isStatic;
}

void C_Transform::AddPosition(float x, float y) {
    position.x += x;
    position.y += y;
}

void C_Transform::AddPosition(const sf::Vector2f& pos) {
    position += pos;
}

void C_Transform::SetX(float x) {
    position.x = x;
}

void C_Transform::SetY(float y) {
    position.y = y;
}

void C_Transform::AddX(float x) {
    position.x += x;
}

void C_Transform::AddY(float y) {
    position.y += y;
}

bool C_Transform::IsStatic() const {
    return isStaticTransform;
}

const sf::Vector2f& C_Transform::GetPosition() const {
    return position;
}