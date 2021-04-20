#ifndef Window_hpp
#define Window_hpp

#include <SFML/Graphics.hpp>
#include <vector>

class Window {
public:
    Window(const std::string& windowName);

    void Update();

    void BeginDraw();
    void Draw(const sf::Drawable& drawable);
    void EndDraw();

    bool IsOpen() const;
    sf::Vector2u GetCentre() const;
    void Draw(const std::vector<sf::Vertex>& vertices,
        std::size_t vertexCount, sf::PrimitiveType type);

private:
    sf::RenderWindow window;

};

#endif /* Window_hpp */