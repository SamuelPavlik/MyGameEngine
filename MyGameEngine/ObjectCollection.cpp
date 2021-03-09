#include "ObjectCollection.hpp"
#include <algorithm>

void ObjectCollection::Update(float deltaTime) {
    for (auto& o : objects) {
        o->Update(deltaTime);
    }
}

void ObjectCollection::LateUpdate(float deltaTime) {
    for (auto& o : objects) {
        o->LateUpdate(deltaTime);
    }
}

void ObjectCollection::Draw(Window& window) {
    for (auto& o : objects) {
        o->Draw(window);
    }
}

void ObjectCollection::Add(std::shared_ptr<Object> object) {
    newObjects.push_back(object);
}

void ObjectCollection::Add(std::vector<std::shared_ptr<Object>> objects) {
    newObjects.insert(newObjects.end(), objects.begin(), objects.end());
}

void ObjectCollection::ProcessNewObjects() {
    if (newObjects.size() > 0) {
        for (const auto& o : newObjects) {
            o->Awake();
        }

        for (const auto& o : newObjects) {
            o->Start();
        }

        objects.insert(objects.end(), newObjects.begin(), newObjects.end());
        newObjects.clear();
    }
}

void ObjectCollection::ProcessRemovals() {
    std::remove_if(objects.begin(), objects.end(),
        [](std::shared_ptr<Object> obj) { return obj->IsQueuedForRemoval(); });

    //auto objIterator = objects.begin();
    //while (objIterator != objects.end()) {
    //    auto obj = **objIterator;

    //    if (obj.IsQueuedForRemoval()) {
    //        objIterator = objects.erase(objIterator);
    //    }
    //    else {
    //        ++objIterator;
    //    }
    //}
}