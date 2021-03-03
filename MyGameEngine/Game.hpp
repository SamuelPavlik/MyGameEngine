#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "WorkingDirectory.hpp"

class Game {
public:
    Game();
    void Update();
    void LateUpdate();
    void Draw();
    bool IsRunning() const;
    void CalculateDeltaTime();

private:
    Window window;
    WorkingDirectory workingDir;

    //Game textures
    sf::Texture vikingTexture;
    sf::Sprite vikingSprite;

    //Time related
    sf::Clock clock;
    float deltaTime;
};


#endif /* Game_hpp */