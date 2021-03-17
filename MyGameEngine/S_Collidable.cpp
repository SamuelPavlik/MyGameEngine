#include "S_Collidable.hpp"
#include "Object.hpp"
#include "C_BoxCollider.hpp"

#include <algorithm>

S_Collidable::S_Collidable() {
    Bitmask defaultCollisions;
    defaultCollisions.SetBit((int)CollisionLayer::Default);
    collisionLayers.insert(
        std::make_pair(CollisionLayer::Default, defaultCollisions));

    collisionLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask()));

    Bitmask playerCollisions;
    playerCollisions.SetBit((int)CollisionLayer::Default);
    playerCollisions.SetBit((int)CollisionLayer::Tile);
    collisionLayers.insert(std::make_pair(CollisionLayer::Player, playerCollisions));
}

void S_Collidable::Add(std::vector<std::shared_ptr<Object>>& objects) {
    for (auto obj : objects) {
        auto collider = obj->GetComponent<C_BoxCollider>();
        if (collider) {
            collidables[collider->GetLayer()].push_back(collider);
        }
    }
}

void S_Collidable::ProcessRemovals() {
    for (auto& layer : collidables) {
        std::remove_if(layer.second.begin(), layer.second.end(), [](auto coll) {
            return coll->owner->IsQueuedForRemoval();
        });
    }
}

void S_Collidable::Update() {
    collisionTree.Clear();
    for (auto& maps : collidables) {
        for (auto& collidable : maps.second) {
            collisionTree.Insert(collidable);
        }
    }

    Resolve();
}

void S_Collidable::Resolve() {
    for (auto maps : collidables) {
        // If this layer collides with nothing then no need to 
        // perform any further checks.
        if (collisionLayers[maps.first].GetMask() == 0) {
            continue;
        }

        for (auto collidableObj : maps.second) {
            // If this collidable is static then no need to check if 
            // it's colliding with other objects.
            if (collidableObj->owner->transform->IsStatic()) {
                continue;
            }

            std::vector<std::shared_ptr<C_BoxCollider>> collisions =
                collisionTree.Search(collidableObj->GetCollidable());

            for (auto collisionObj : collisions) {
                // Make sure we do not resolve collisions between the same object.
                if (collidableObj->owner->GetInstanceID() 
                    == collisionObj->owner->GetInstanceID()) {
                    continue;
                }

                bool areLayersColliding = collisionLayers[collidableObj->GetLayer()]
                    .GetBit(((int)collisionObj->GetLayer()));

                if (areLayersColliding) {
                    Manifold m = collidableObj->Intersects(collisionObj);

                    if (m.colliding) {
                        if (collisionObj->owner->transform->IsStatic()) {
                            collidableObj->ResolveOverlap(m);
                        }
                        else {
                            //TODO: How should we handle collisions when both 
                            // objects are not static?
                            // We could implement rigidbodies and mass.
                            collidableObj->ResolveOverlap(m);
                        }

                    }
                }
            }

        }
    }
}
