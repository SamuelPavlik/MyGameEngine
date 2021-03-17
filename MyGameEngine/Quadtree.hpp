#ifndef Quadtree_hpp
#define Quadtree_hpp

#include <memory>
#include <vector>
#include <array>

#include "Object.hpp"

class C_BoxCollider;

class Quadtree {
public:
    Quadtree();
    Quadtree(int maxObjects, int maxLevels, int level,
        sf::FloatRect bounds, Quadtree* parent);

    // Inserts object into our quadtree.
    void Insert(std::shared_ptr<C_BoxCollider> object);

    // Removes object from our quadtree when we no longer need it to collide.
    void Remove(std::shared_ptr<C_BoxCollider> object);

    // Removes all objects from tree.
    void Clear();

    // Returns vector of colliders that intersect with the search area.
    std::vector<std::shared_ptr<C_BoxCollider>>
        Search(const sf::FloatRect& area);

    // Returns the bounds of this node.
    const sf::FloatRect& GetBounds() const;

private:
    void SearchInArea(const sf::FloatRect& area, 
        std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects);

    // Returns the index for the node that will contain 		
    // the object. -1 is returned if it is this node.
    int GetChildIndexForObject(const sf::FloatRect& objectBounds);

    // Creates the child nodes.
    void Split();

    static const int thisTree = -1;
    static const int childNE = 0;
    static const int childNW = 1;
    static const int childSW = 2;
    static const int childSE = 3;

    int maxObjects;
    int maxLevels;

    Quadtree* parent;
    std::array<std::shared_ptr<Quadtree>, 4> children;
    std::vector<std::shared_ptr<C_BoxCollider>> objects;
    int level;
    sf::FloatRect bounds;
};

#endif /* Quadtree_hpp */