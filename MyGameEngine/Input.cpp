#include "Input.hpp"


Input::Input() {
    //empty element for zero position which will be disregarded
    keyToPosMapping.push_back("");
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

void Input::AddMapping(std::string KeyName, sf::Keyboard::Key keyInput) {
    static unsigned last_pos = 0;
    keyToPosMapping.push_back(KeyName);
    posToKeyboardMapping[last_pos].push_back(keyInput);
}

// Return true if the specified key is currently being pressed.
bool Input::IsKeyPressed(Key keycode) {
    return thisFrameKeys.GetBit((int)keycode);
}

// Returns true if the key was just pressed 
// (i.e. registered as pressed this frame but not the previous).
bool Input::IsKeyDown(Key keycode) {
    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);

    return thisFrame && !lastFrame;
}

// Returns true if the key was just released (i.e. registered as 
// pressed last frame but not the current frame).
bool Input::IsKeyUp(Key keycode) {
    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);

    return !thisFrame && lastFrame;
}
