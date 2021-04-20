#include "S_Drawable.hpp"
#include "Object.hpp"

#include <algorithm>

S_Drawable::S_Drawable() {
    drawablesMap = DrawablesMap();
}

void S_Drawable::Add(std::vector<std::shared_ptr<Object>>& objects) {
    for (auto& o : objects) {
        Add(o);
    }
}

void S_Drawable::ProcessRemovals() {
    for (auto& layer : drawablesMap) {
        std::remove_if(layer.second.begin(), layer.second.end(), [](auto& drawable) {
            return drawable->IsQueuedForRemoval();
        });
    }
}

void S_Drawable::Draw(Window& window) {
    Sort();

    for (auto& layer : drawablesMap) {
        for (auto& drawable : layer.second) {
            drawable->Draw(window);
        }
    }
}

void S_Drawable::Add(std::shared_ptr<Object>& object) {
    if (const auto& sprite = object->GetDrawable()) {
        drawablesMap[sprite->GetDrawLayer()].push_back(sprite);
    }
}

const auto compareFunc = [](const std::shared_ptr<C_Drawable>& a, const std::shared_ptr<C_Drawable>& b) {
    return a->GetSortOrder() < b->GetSortOrder();
};

void S_Drawable::Sort() {
    for (auto& layer : drawablesMap) {
        if (!std::is_sorted(layer.second.begin(), layer.second.end())) {
            std::sort(layer.second.begin(), layer.second.end(), compareFunc);
        }
    }
}
