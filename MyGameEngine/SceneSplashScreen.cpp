#include "SceneSplashScreen.hpp"
#include "SceneStateMachine.hpp"
#include "WorkingDirectory.hpp"
#include "ResourceAllocator.hpp"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDir,
    SceneStateMachine& sceneStateMachine,
    Window& window, ResourceAllocator<sf::Texture>& textureAllocator) :
    sceneStateMachine(sceneStateMachine), 
    workingDir(workingDir),
    window(window), 
    textureAllocator(textureAllocator),
    switchToState(0), 
    currentSeconds(0.f),
    showForSeconds(3.f) {}

void SceneSplashScreen::OnCreate() {
    int textureID = textureAllocator.Add(workingDir.Get()
        + "TanksCover.PNG");

    if (textureID >= 0) {
        std::shared_ptr<sf::Texture> texture = textureAllocator.Get(textureID);
        splashSprite.setTexture(*texture);

        sf::FloatRect spriteSize = splashSprite.getLocalBounds();

        // Set the origin of the sprite to the centre of the image:
        splashSprite.setOrigin(spriteSize.width * 0.5f,
            spriteSize.height * 0.5f);
        splashSprite.setScale(0.5f, 0.5f);

        sf::Vector2u windowCentre = window.GetCentre();

        // Positions sprite in centre of screen:
        splashSprite.setPosition(windowCentre.x, windowCentre.y);
    }
}

void SceneSplashScreen::OnActivate() {
    currentSeconds = 0.f;
}

void SceneSplashScreen::OnDestroy() {}

void SceneSplashScreen::SetSwitchToScene(unsigned int id) {
    switchToState = id;
}

void SceneSplashScreen::Update(float deltaTime) {
    currentSeconds += deltaTime;

    if (currentSeconds >= showForSeconds) {
        sceneStateMachine.SwitchTo(switchToState);
    }
}

void SceneSplashScreen::Draw(Window& window) {
    window.Draw(splashSprite);
}