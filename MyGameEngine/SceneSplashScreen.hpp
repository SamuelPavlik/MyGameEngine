#ifndef SceneSplashScreen_hpp
#define SceneSplashScreen_hpp

#include "Scene.hpp"

#include <SFML/Graphics.hpp>

class WorkingDirectory;
class SceneStateMachine;
class Window;
template<typename T>
class ResourceAllocator;

class SceneSplashScreen : public Scene {
public:
    SceneSplashScreen(const WorkingDirectory& workingDir,
        SceneStateMachine& sceneStateMachine, Window& window, 
        ResourceAllocator<sf::Texture>& textureAllocator);

    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;

    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw(Window& window) override;

private:
    sf::Sprite splashSprite;

    const WorkingDirectory& workingDir;
    SceneStateMachine& sceneStateMachine;
    Window& window;
    ResourceAllocator<sf::Texture>& textureAllocator;

    float showForSeconds;
    float currentSeconds;
    unsigned int switchToState;
};

#endif /* SceneSplashScreen_hpp */