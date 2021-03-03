#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"

class Game
{
public:
    Game() : window("Game Window") {}
    void Update();
    void LateUpdate();
    void Draw();
    bool IsRunning() const;

private:
    Window window;
};


#endif /* Game_hpp */