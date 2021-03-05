#include "C_Sprite.hpp"
#include "Object.hpp"
#include "C_Transform.hpp"

C_Sprite::C_Sprite(Object* owner, ResourceAllocator<sf::Texture>* allocator, const std::string& filePath) : 
    Component(owner), 
    allocator(allocator) {
    if (allocator) {
        int textureID = allocator->Add(filePath);
        if (textureID >= 0) {
            std::shared_ptr<sf::Texture> texture = allocator->Get(textureID);
            sprite.setTexture(*texture);
        }
    }
}

void C_Sprite::Load(const std::string& filePath) {
    //texture.loadFromFile(filePath);
    //sprite.setTexture(texture);
}

void C_Sprite::Draw(Window& window) {
    window.Draw(sprite);
}

void C_Sprite::LateUpdate(float DeltaTime) {
    sprite.setPosition(owner->transform->GetPosition());
}
