#ifndef Scene_hpp
#define Scene_hpp

#include "Window.hpp"

class Scene {
public:
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnActivate() {};
	virtual void OnDeactivate() {};

	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
	virtual void Draw(Window& window) {};
};


#endif /* Scene_hpp */