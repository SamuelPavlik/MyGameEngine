#ifndef C_Sprite_hpp
#define C_Sprite_hpp

#include "Component.hpp"
#include "C_Drawable.hpp"

template<typename T>
class ResourceAllocator;

class C_Sprite : public Component, public C_Drawable {
public:
    C_Sprite(Object* owner, ResourceAllocator<sf::Texture>* allocator);

    C_Sprite(Object* owner, ResourceAllocator<sf::Texture>* allocator, const std::string& filePath);

    void Load(const std::string& filePath);

    void Load(int id);

    void Draw(Window& window) override;

    void LateUpdate(float DeltaTime) override;

    void SetTextureRect(int x, int y, int width, int height);

    void SetTextureRect(const sf::IntRect& rect);

    void SetScale(float x, float y);

private:
    ResourceAllocator<sf::Texture>* allocator;
    sf::Sprite sprite;
    int currentTextureID;
};

#endif /* C_Sprite_hpp */