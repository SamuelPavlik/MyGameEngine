#include "C_Sprite.hpp"
#include "Object.hpp"
#include "C_Transform.hpp"
#include "ResourceAllocator.hpp"

C_Sprite::C_Sprite(Object* owner, ResourceAllocator<sf::Texture>* allocator) :
    Component(owner),
    allocator(allocator),
    currentTextureID(-1) {}

C_Sprite::C_Sprite(Object* owner, ResourceAllocator<sf::Texture>* allocator, const std::string& filePath) : 
    C_Sprite(owner, allocator) {
    Load(filePath);
}

void C_Sprite::Load(const std::string& filePath) {
    if (allocator) {
        int textureID = allocator->Add(filePath);
        if (textureID >= 0 && textureID != currentTextureID) {
            std::shared_ptr<sf::Texture> texture = allocator->Get(textureID);
            sprite.setTexture(*texture);
        }
    }
}

void C_Sprite::Load(int id) {
    if (id >= 0 && id != currentTextureID) {
        std::shared_ptr<sf::Texture> texture = allocator->Get(id);
        sprite.setTexture(*texture);
    }
}

void C_Sprite::Draw(Window& window) {
    window.Draw(sprite);
}

void C_Sprite::LateUpdate(float DeltaTime) {
    sprite.setPosition(owner->transform->GetPosition());
}

void C_Sprite::SetTextureRect(int x, int y, int width, int height) {
    sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void C_Sprite::SetTextureRect(const sf::IntRect& rect) {
    sprite.setTextureRect(rect);
}

void C_Sprite::SetScale(float x, float y) {
    sprite.setScale(x, y);
}
