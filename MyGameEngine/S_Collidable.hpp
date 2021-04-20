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

    std::map<CollisionLayer, Bitmask> collisionLayers;
    std::map<CollisionLayer, std::vector<std::shared_ptr<C_BoxCollider>>> collidables;
    Quadtree collisionTree;
};

#endif /* S_Collidable_hpp */