#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "Scene.hpp"
#include "ObjectCollection.hpp"
#include "TileMapParser.hpp"

class Object;
class Input;
class WorkingDirectory;
template<typename T>
class ResourceAllocator;

class SceneGame : public Scene {
public:
    SceneGame(const WorkingDirectory& workingDir, Input& input, ResourceAllocator<sf::Texture>& textureAllocator);

    void OnCreate() override;
    void OnDestroy() override;

    void Update(float deltaTime) override;
    void Draw(Window& window) override;
    void LateUpdate(float deltaTime) override;

private:
    const WorkingDirectory& workingDir;
    Input& input;
    ResourceAllocator<sf::Texture>& textureAllocator;
    ObjectCollection objects;
    TileMapParser mapParser;
};

#endif /* SceneGame_hpp */