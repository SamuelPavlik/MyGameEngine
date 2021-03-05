#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "Scene.hpp"

class Object;
class Input;
class WorkingDirectory;

class SceneGame : public Scene {
public:
    SceneGame(WorkingDirectory& workingDir, Input& input);

    void OnCreate() override;
    void OnDestroy() override;

    void Update(float deltaTime) override;
    void Draw(Window& window) override;
    void LateUpdate(float deltaTime) override;

private:
    std::shared_ptr<Object> player;

    WorkingDirectory& workingDir;
    Input& input;
};

#endif /* SceneGame_hpp */