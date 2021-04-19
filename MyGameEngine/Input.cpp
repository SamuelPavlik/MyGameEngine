#include "Input.hpp"

Input::Input() {
    posToKeyboardMapping.push_back(std::vector<sf::Keyboard::Key>());
}

void Input::Update() {
    lastFrameKeys.SetMask(thisFrameKeys);
    for (size_t i = 1; i < keyToPosMapping.size(); i++) {
        bool result = false;
        for (const auto& keyb : posToKeyboardMapping[i]) {
            result = result || sf::Keyboard::isKeyPressed(keyb);
        }
        thisFrameKeys.SetBit(i, result);
    }
}

void Input::AddMapping(std::string keyName, sf::Keyboard::Key keyInput) {
    static size_t last_pos = 1;
    if (keyToPosMapping.find(keyName) == keyToPosMapping.end()) {
        keyToPosMapping[keyName] = last_pos++;
        posToKeyboardMapping.push_back(std::vector<sf::Keyboard::Key>{ keyInput });
    }
    else {
        posToKeyboardMapping[keyToPosMapping[keyName]].push_back(keyInput);
    }
}

// Return true if the specified key is currently being pressed.
bool Input::IsKeyPressed(std::string keyName) {
    return thisFrameKeys.GetBit(keyToPosMapping[keyName]);
}

// Returns true if the key was just pressed 
// (i.e. registered as pressed this frame but not the previous).
bool Input::IsKeyDown(std::string keyName) {
    bool lastFrame = lastFrameKeys.GetBit(keyToPosMapping[keyName]);
    bool thisFrame = thisFrameKeys.GetBit(keyToPosMapping[keyName]);

    return thisFrame && !lastFrame;
}

// Returns true if the key was just released (i.e. registered as 
// pressed last frame but not the current frame).
bool Input::IsKeyUp(std::string keyName) {
    bool lastFrame = lastFrameKeys.GetBit(keyToPosMapping[keyName]);
    bool thisFrame = thisFrameKeys.GetBit(keyToPosMapping[keyName]);

    return !thisFrame && lastFrame;
}
