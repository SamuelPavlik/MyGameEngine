#ifndef S_Collidable_hpp
#define S_Collidable_hpp

#include <memory>
#include <map>

#include "Quadtree.hpp"
#include "Bitmask.hpp"
#include "C_Collider.hpp"

class Object;

class S_Collidable {
public:
    S_Collidable();

    void Add(std::vector<std::shared_ptr<Object>>& objects);
    void ProcessRemovals();
    void Update();

private:
    void Resolve();
    void ProcessCollisions(std::vector<std::shared_ptr<Object>>& first, std::vector<std::shared_ptr<Object>>& second);

    // This is used to store collision layer data i.e. which layers can collide.
    std::map<CollisionLayer, Bitmask> collisionLayers;

    // The collision system stores all collidables along with their layer.
    std::map<CollisionLayer, std::vector<std::shared_ptr<C_BoxCollider>>> collidables;

    // The quadtree stores the collidables in a spatial aware structure.
    Quadtree collisionTree;
};

#endif /* S_Collidable_hpp */