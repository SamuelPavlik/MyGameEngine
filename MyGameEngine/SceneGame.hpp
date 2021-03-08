#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "Scene.hpp"
#include "ResourceAllocator.hpp"
#include "ObjectCollection.hpp"

class Object;
class Input;
class WorkingDirectory;

class SceneGame : public Scene {
public:
    SceneGame(WorkingDirectory& workingDir, Input& input, ResourceAllocator<sf::Texture>& textureAllocator);

    void OnCreate() override;
    void OnDestroy() override;

    void Update(float deltaTime) override;
    void Draw(Window& window) override;
    void LateUpdate(float deltaTime) override;

private:
    std::shared_ptr<Object> player;

    WorkingDirectory& workingDir;
    Input& input;
    ResourceAllocator<sf::Texture>& textureAllocator;
    ObjectCollection objects;
};

#endif /* SceneGame_hpp */