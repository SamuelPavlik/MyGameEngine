#include "S_Drawable.hpp"

#include <algorithm>

void S_Drawable::Add(std::vector<std::shared_ptr<Object>>& objects) {
    for (auto& o : objects) Add(o);
    //Sort();
}

void S_Drawable::ProcessRemovals() {
    for (auto i = drawables.begin(), last = drawables.end(); i != last; ) {
        if ((*i)->IsQueuedForRemoval())
            i = drawables.erase(i);
        else
            ++i;
    }
    //std::remove_if(drawables.begin(), drawables.end(), 
    //    [](auto elem) { return elem->IsQueuedForRemoval(); });
}

void S_Drawable::Draw(Window& window) {
    for (auto& d : drawables) d->Draw(window);
}

void S_Drawable::Add(std::shared_ptr<Object> object) {
    if (object->GetDrawable()) {
        drawables.insert(object);
    }
}

//void S_Drawable::Sort() {
//    std::sort(drawables.begin(), drawables.end(),
//        [](auto a, auto b) {
//            return a->GetDrawable()->GetSortOrder()
//                < b->GetDrawable()->GetSortOrder();
//        }
//    );
//}