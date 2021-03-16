#include "Quadtree.hpp"
#include "C_BoxCollider.hpp"

#include <algorithm>

Quadtree::Quadtree() : Quadtree(5, 5, 0, { 0.f, 0.f, 1920, 1080 },
	nullptr) {
}

Quadtree::Quadtree(int maxObjects, int maxLevels, int level,
	sf::FloatRect bounds, Quadtree* parent)
	: maxObjects(maxObjects), maxLevels(maxLevels),
	level(level), bounds(bounds), parent(parent) {
}

void Quadtree::Insert(std::shared_ptr<C_BoxCollider> object) {
    if (children[0] != nullptr) {
        int indexToPlaceObject =
            GetChildIndexForObject(object->GetCollidable());

        if (indexToPlaceObject != thisTree) {
            children[indexToPlaceObject]->Insert(object);
            return;
        }
    }

    objects.emplace_back(object);

    if (objects.size() > maxObjects &&
        level < maxLevels && children[0] == nullptr) {
        Split();

        std::remove_if(objects.begin(), objects.end(), [this](auto obj) {
            int indexToPlaceObject =
                GetChildIndexForObject(obj->GetCollidable());

            if (indexToPlaceObject != thisTree) {
                children[indexToPlaceObject]->Insert(obj);
                return true;
            }
            return false;
        });
        /*auto objIterator = objects.begin();
        while (objIterator != objects.end()) {
            auto obj = *objIterator;
            int indexToPlaceObject =
                GetChildIndexForObject(obj->GetCollidable());

            if (indexToPlaceObject != thisTree) {
                children[indexToPlaceObject]->Insert(obj);
                objIterator = objects.erase(objIterator);

            }
            else             {
                ++objIterator;
            }
        }*/
    }
}

void Quadtree::Remove(std::shared_ptr<C_BoxCollider> object) {
    int index = GetChildIndexForObject(object->GetCollidable());

    //TODO possibly out of bounds exception for children[index]
    if (index == thisTree || children[index] == nullptr) {
        for (auto objIter = objects.begin(); objIter != objects.end(); objIter++) {
            if ((*objIter)->owner->GetInstanceID() == object->owner->GetInstanceID()) {
                objects.erase(objIter);
                break;
            }
        }
    }
    else {
        return children[index]->Remove(object);
    }
}

void Quadtree::Clear() {
    objects.clear();
    for (auto &child : children) {
        if (child != nullptr) {
            child->Clear();
            child = nullptr;
        }
    }
}

int Quadtree::GetChildIndexForObject(const sf::FloatRect& objectBounds) {
    return 0;
}

void Quadtree::Split() {
}
