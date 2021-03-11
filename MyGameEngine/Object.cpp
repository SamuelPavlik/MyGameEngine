#include "Object.hpp"
#include "C_Drawable.hpp"

Object::Object() : queuedForRemoval(false) {
    transform = AddComponent<C_Transform>();
}

void Object::Awake() {
    for (int i = components.size() - 1; i >= 0; i--) {
        components[i]->Awake();
    }
}

void Object::Start() {
    for (int i = components.size() - 1; i >= 0; i--) {
        components[i]->Start();
    }
}

void Object::Update(float timeDelta) {
    for (int i = components.size() - 1; i >= 0; i--) {
        components[i]->Update(timeDelta);
    }
}

void Object::LateUpdate(float timeDelta) {
    for (int i = components.size() - 1; i >= 0; i--) {
        components[i]->LateUpdate(timeDelta);
    }
}

void Object::Draw(Window& window) {
    drawable->Draw(window);
}

void Object::QueueForRemoval() {
    queuedForRemoval = true;
}

std::shared_ptr<C_Drawable> Object::GetDrawable() const {
    return drawable;
}

bool Object::IsQueuedForRemoval() const {
    return queuedForRemoval;
}