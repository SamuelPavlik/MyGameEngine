#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "WorkingDirectory.hpp"
#include "Input.hpp"
#include "SceneStateMachine.hpp"

class Game {
public:
    Game();
    void Update();
    void LateUpdate();
    void Draw();
    bool IsRunning() const;
    void CalculateDeltaTime();
    void CaptureInput();

private:
    Window window;
    WorkingDirectory workingDir;

    //Game textures
    sf::Texture vikingTexture;
    sf::Sprite vikingSprite;

    //Time related
    sf::Clock clock;
    float deltaTime;

    //Input managment
    Input input;

    //Scene managment
    SceneStateMachine sceneStateMachine;
};


#endif /* Game_hpp */