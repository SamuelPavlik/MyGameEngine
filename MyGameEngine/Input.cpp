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

void Input::AddMapping(const std::string& keyName, sf::Keyboard::Key keyInput) {
    static size_t last_pos = 1;
    if (keyToPosMapping.find(keyName) == keyToPosMapping.end()) {
        keyToPosMapping[keyName] = last_pos++;
        posToKeyboardMapping.push_back(std::vector<sf::Keyboard::Key>{ keyInput });
    }
    else {
        posToKeyboardMapping[keyToPosMapping[keyName]].push_back(keyInput);
    }
}

bool Input::IsKeyPressed(const std::string& keyName) const {
    auto it = keyToPosMapping.find(keyName);
    if (it != keyToPosMapping.end()) {
        return thisFrameKeys.GetBit(it->second);
    }
    return false;
}

bool Input::IsKeyDown(const std::string& keyName) const {
    auto it = keyToPosMapping.find(keyName);
    if (it != keyToPosMapping.end()) {
        bool lastFrame = lastFrameKeys.GetBit(it->second);
        bool thisFrame = thisFrameKeys.GetBit(it->second);
        return thisFrame && !lastFrame;
    }
    return false;
}

bool Input::IsKeyUp(const std::string& keyName) const {
    auto it = keyToPosMapping.find(keyName);
    if (it != keyToPosMapping.end()) {
        bool lastFrame = lastFrameKeys.GetBit(it->second);
        bool thisFrame = thisFrameKeys.GetBit(it->second);
        return !thisFrame && lastFrame;
    }
    return false;
}
