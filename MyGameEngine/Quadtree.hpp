#ifndef Quadtree_hpp
#define Quadtree_hpp

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <array>

class C_BoxCollider;

class Quadtree {
public:
    Quadtree();
    Quadtree(int maxObjects, int maxLevels, int level,
        sf::FloatRect bounds, Quadtree* parent);

    void Insert(std::shared_ptr<C_BoxCollider>& object);
    void Remove(std::shared_ptr<C_BoxCollider>& object);
    void Clear();
    std::vector<std::shared_ptr<C_BoxCollider>>
        Search(const sf::FloatRect& area);

    const sf::FloatRect& GetBounds() const;
    const bool ContainsNull() const;

    void DrawDebug() const;

private:
    void SearchInArea(const sf::FloatRect& area, 
        std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects) const;
    int GetChildIndexForObject(const sf::FloatRect& objectBounds) const;

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
    int level;
    sf::FloatRect bounds;

public:
    std::vector<std::shared_ptr<C_BoxCollider>> objects;
};

#endif /* Quadtree_hpp */