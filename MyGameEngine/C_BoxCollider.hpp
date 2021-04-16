#ifndef C_BoxCollider_hpp
#define C_BoxCollider_hpp

#include "C_Collider.hpp"

class C_BoxCollider : public C_Collider {
public:
    C_BoxCollider(Object* owner);
    C_BoxCollider(Object* owner, sf::FloatRect AABB, 
        CollisionLayer layer = CollisionLayer::Default, 
        sf::Vector2f offset = sf::Vector2f(0.f, 0.f));

    Manifold Intersects(const std::shared_ptr<C_Collider>& other) override;
    void ResolveOverlap(const Manifold& m) override;

    void SetCollidable(const sf::FloatRect& rect);
    void SetLayer(CollisionLayer layer);
    const sf::FloatRect& GetCollidable();

private:
    void SetPosition();
    
    static sf::FloatRect GetIntersectionRect(const sf::FloatRect& rect1, 
        const sf::FloatRect& rect2);

    sf::FloatRect AABB;
    CollisionLayer layer;
    sf::Vector2f offset;
};

#endif /* C_BoxCollider_hpp */