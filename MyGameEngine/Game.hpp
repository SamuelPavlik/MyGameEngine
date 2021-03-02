#ifndef Game_hpp
#define Game_hpp

class Game
{
public:
    void Update();
    void LateUpdate();
    void Draw();
    bool IsRunning() const;
};

#endif /* Game_hpp */