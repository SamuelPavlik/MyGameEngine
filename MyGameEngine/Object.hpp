#ifndef Object_hpp
#define Object_hpp

#include "Window.hpp"
#include "Component.hpp"
#include "C_Transform.hpp"

class C_Drawable;

class Object {
public:
    Object();

    // Awake is called when object created. Use to ensure 
    // required components are present.
    void Awake();

    // Start is called after Awake method. Use to initialise variables.
    void Start();

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);
    bool IsQueuedForRemoval() const;
    void QueueForRemoval();
    std::shared_ptr<C_Drawable> GetDrawable() const;
    const size_t GetInstanceID() const;

    template <typename T, typename... Args> std::shared_ptr<T> AddComponent(Args... args) {
        static_assert(std::is_base_of<Component, T>::value,
            "T must derive from Component");

        // Check that we don't already have a component of this type
        for (auto& exisitingComponent : components) {
            if (std::dynamic_pointer_cast<T>(exisitingComponent)) {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this, args...);
        components.push_back(newComponent);

        // Check if the component is a drawable
        if (std::dynamic_pointer_cast<C_Drawable>(newComponent)) {
            drawable = std::dynamic_pointer_cast<C_Drawable>(newComponent);
        }

        return newComponent;
    };

    template <typename T> std::shared_ptr<T> GetComponent() {
        static_assert(std::is_base_of<Component, T>::value,
            "T must derive from Component");

        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components) {
            if (std::dynamic_pointer_cast<T>(exisitingComponent)) {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }

        return nullptr;
    };

public:
    std::shared_ptr<C_Transform> transform;
    bool queuedForRemoval;

private:
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<C_Drawable> drawable;
    size_t instanceID;

    static size_t count;
};

#endif /* Object_hpp */