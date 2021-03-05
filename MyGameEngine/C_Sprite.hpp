#ifndef C_Sprite_hpp
#define C_Sprite_hpp

#include "Component.hpp"
#include "ResourceAllocator.hpp"

class C_Sprite : public Component {
public:
    C_Sprite(Object* owner, ResourceAllocator<sf::Texture>* allocator, const std::string& filePath);

    void Load(const std::string& filePath);

    void Draw(Window& window) override;

    void LateUpdate(float DeltaTime) override;

private:
    ResourceAllocator<sf::Texture>* allocator;
    sf::Sprite sprite;
    //sf::Texture texture;
};

#endif /* C_Sprite_hpp */