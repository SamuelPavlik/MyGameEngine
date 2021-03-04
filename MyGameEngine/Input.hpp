#ifndef Input_hpp
#define Input_hpp

#include "Bitmask.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>

class Input {
public:
    enum class Key {
        None = 0,
        Left = 1,
        Right = 2,
        Up = 3,
        Down = 4,
        Esc = 5
    };
    Input();
    void Update();
    void AddMapping(std::string keyName, sf::Keyboard::Key keyInput);
    bool IsKeyPressed(std::string keyName); // Returns true if the key is pressed.
    bool IsKeyDown(std::string keyName); // Returns true if the key was just pressed.
    bool IsKeyUp(std::string keyName); // Returns true if the key was just released.

private:
    Bitmask thisFrameKeys;
    Bitmask lastFrameKeys;
    std::unordered_map<std::string, size_t> keyToPosMapping;
    std::vector<std::vector<sf::Keyboard::Key>> posToKeyboardMapping;
};

#endif /* Input_hpp */