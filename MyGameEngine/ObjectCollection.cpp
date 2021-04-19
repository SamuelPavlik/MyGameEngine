#include "ObjectCollection.hpp"

#include <algorithm>

void ObjectCollection::Update(float deltaTime) {
    for (auto& o : objects) {
        o->Update(deltaTime);
    }
    collidables.Update();
}

void ObjectCollection::LateUpdate(float deltaTime) {
    for (auto& o : objects) {
        o->LateUpdate(deltaTime);
    }
}

void ObjectCollection::Draw(Window& window) {
    drawables.Draw(window);
}

void ObjectCollection::Add(std::shared_ptr<Object>& object) {
    newObjects.push_back(object);
}

void ObjectCollection::Add(std::vector<std::shared_ptr<Object>>& objects) {
    newObjects.insert(newObjects.end(), objects.begin(), objects.end());
}

void ObjectCollection::ProcessNewObjects() {
    if (newObjects.size() > 0) {
        for (auto& o : newObjects) {
            o->Awake();
        }

        for (auto& o : newObjects) {
            o->Start();
        }

        objects.insert(objects.end(), newObjects.begin(), newObjects.end());
        drawables.Add(newObjects);
        collidables.Add(newObjects);
        newObjects.clear();
    }
}

void ObjectCollection::ProcessRemovals() {
    bool isRemovedSth = false;
    auto newEnd = std::remove_if(objects.begin(), objects.end(),
        [&isRemovedSth](std::shared_ptr<Object> obj) { 
            if (obj->IsQueuedForRemoval()) {
                isRemovedSth = true;
                return true;
            }
            return false; 
        });
    objects.erase(newEnd, objects.end());

    if (isRemovedSth) {
        drawables.ProcessRemovals();
        collidables.ProcessRemovals();
    }
}