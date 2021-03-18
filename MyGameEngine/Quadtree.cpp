#include "Quadtree.hpp"
#include "C_BoxCollider.hpp"
#include "Object.hpp"

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

        auto newEnd = std::remove_if(objects.begin(), objects.end(), [this](auto obj) {
            int indexToPlaceObject =
                GetChildIndexForObject(obj->GetCollidable());

            if (indexToPlaceObject != thisTree) {
                children[indexToPlaceObject]->Insert(obj);
                return true;
            }
            return false;
        });
        objects.erase(newEnd, objects.end());
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

std::vector<std::shared_ptr<C_BoxCollider>> Quadtree::Search(const sf::FloatRect& area) {
    std::vector<std::shared_ptr<C_BoxCollider>> possibleOverlaps;
    SearchInArea(area, possibleOverlaps);
    std::vector<std::shared_ptr<C_BoxCollider>> returnList;

    for (auto collider : possibleOverlaps) {
        if (area.intersects(collider->GetCollidable())) {
            returnList.emplace_back(collider);
        }
    }

    return returnList;
}

const sf::FloatRect& Quadtree::GetBounds() const {
    return bounds;
}

const bool Quadtree::ContainsNull() const {
    for (auto& child : children) {
        if (child && child->ContainsNull())
            return true;
    }
    return std::find(objects.begin(), objects.end(), nullptr) != objects.end();
}

void Quadtree::SearchInArea(const sf::FloatRect& area,
    std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects) {
    overlappingObjects.insert(overlappingObjects.end(), objects.begin(), objects.end());

    if (children[0] != nullptr) {
        int index = GetChildIndexForObject(area);

        if (index == thisTree) {
            for (int i = 0; i < 4; i++) {
                if (children[i]->GetBounds().intersects(area)) {
                    children[i]->SearchInArea(area, overlappingObjects);
                }
            }
        }
        else {
            children[index]->SearchInArea(area, overlappingObjects);
        }
    }
}

int Quadtree::GetChildIndexForObject(const sf::FloatRect& objectBounds) {
    int index = -1;

    float verticalDividingLine = bounds.left + bounds.width * 0.5f;
    float horizontalDividingLine = bounds.top + bounds.height * 0.5f;

    bool north = objectBounds.top < horizontalDividingLine
        && (objectBounds.height + objectBounds.top < horizontalDividingLine);
    bool south = objectBounds.top > horizontalDividingLine 
        && (objectBounds.height + objectBounds.top > horizontalDividingLine);
    bool west = objectBounds.left < verticalDividingLine
        && (objectBounds.left + objectBounds.width < verticalDividingLine);
    bool east = objectBounds.left > verticalDividingLine
        && (objectBounds.left + objectBounds.width > verticalDividingLine);

    if (east) {
        if (north) {
            index = childNE;
        }
        else if (south) {
            index = childSE;
        }
    }
    else if (west) {
        if (north) {
            index = childNW;
        }
        else if (south) {
            index = childSW;
        }
    }

    return index;
}

void Quadtree::Split() {
    const int childWidth = bounds.width / 2;
    const int childHeight = bounds.height / 2;

    children[childNE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left + childWidth, bounds.top, childWidth, childHeight),
        this);
    children[childNW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left, bounds.top, childWidth, childHeight),
        this);
    children[childSW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left, bounds.top + childHeight, childWidth, childHeight),
        this);
    children[childSE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left + childWidth, bounds.top + childHeight, childWidth, childHeight),
        this);
}
