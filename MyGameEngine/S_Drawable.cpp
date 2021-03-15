#include "S_Drawable.hpp"

#include <algorithm>

S_Drawable::S_Drawable() {
    auto cmp = [](auto a, auto b) {
        return a->GetDrawable()->GetSortOrder()
            > b->GetDrawable()->GetSortOrder(); };
    drawables = 
        std::multiset<std::shared_ptr<Object>, 
        std::function<bool(std::shared_ptr<Object>, std::shared_ptr<Object>)>>(cmp);
}

void S_Drawable::Add(std::vector<std::shared_ptr<Object>>& objects) {
    for (auto o : objects) Add(o);
}

void S_Drawable::ProcessRemovals() {
    for (auto i = drawables.begin(), last = drawables.end(); i != last; ) {
        if ((*i)->IsQueuedForRemoval())
            i = drawables.erase(i);
        else
            ++i;
    }
}

void S_Drawable::Draw(Window& window) {
    for (auto d : drawables) 
        d->Draw(window);
}

void S_Drawable::Add(std::shared_ptr<Object> object) {
    if (object->GetDrawable()) {
        drawables.insert(object);
    }
}