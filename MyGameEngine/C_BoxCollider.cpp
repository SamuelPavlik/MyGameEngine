#include "C_BoxCollider.hpp"
#include "Object.hpp"

C_BoxCollider::C_BoxCollider(Object* owner) : 
    C_Collider(owner),
    layer(CollisionLayer::Default),
    offset(sf::Vector2f(0.f, 0.f)) {
}

C_BoxCollider::C_BoxCollider(Object* owner, sf::FloatRect AABB,
    CollisionLayer layer, sf::Vector2f offset) :
    C_Collider(owner),
    AABB(AABB),
    layer(layer),
    offset(offset) {}

Manifold C_BoxCollider::Intersects(std::shared_ptr<C_Collider> other) {
    Manifold m;
    std::shared_ptr<C_BoxCollider> boxCollider = 
        std::dynamic_pointer_cast<C_BoxCollider>(other);

    if (boxCollider) {
        const sf::FloatRect& rect1 = GetCollidable();
        const sf::FloatRect& rect2 = boxCollider->GetCollidable();

        if (rect1.intersects(rect2)) {
            m.colliding = true;
            m.other = &rect2;
        }
    }

    return m;
}

void C_BoxCollider::ResolveOverlap(const Manifold& m) {
    auto transform = owner->transform;

    if (transform->IsStatic()) return;

    const sf::FloatRect& rect1 = GetCollidable();
    const sf::FloatRect* rect2 = m.other;

    float resolve = 0;
    float xDiff = (rect1.left + (rect1.width * 0.5f))
        - (rect2->left + (rect2->width * 0.5f));
    float yDiff = (rect1.top + (rect1.height * 0.5f))
        - (rect2->top + (rect2->height * 0.5f));
    auto interRect = GetIntersectionRect(rect1, *rect2);

    //TODO probably reversed and not correct anyway
    //TODO findout intersection rectangle
    if (fabs(interRect.height) > fabs(interRect.width)) {
        if (xDiff > 0) {
            // We add a positive x value to move the object to the right.
            resolve = (rect2->left + rect2->width) - rect1.left;
        }
        else {
            // We add a negative x value to move the object to the left.
            resolve = -((rect1.left + rect1.width) - rect2->left);
        }

        transform->AddPosition(resolve, 0); // 5
    }
    else {
        if (yDiff > 0) {
            // We add a positive y value to move the object down.
            resolve = (rect2->top + rect2->height) - rect1.top;
        }
        else {
            // We add a negative y value to move the object up.
            resolve = -((rect1.top + rect1.height) - rect2->top);
        }

        transform->AddPosition(0, resolve); // 5
    }
}

void C_BoxCollider::SetCollidable(const sf::FloatRect& rect) {
    AABB = rect;
    SetPosition();
}

void C_BoxCollider::SetLayer(CollisionLayer layer) {
    this->layer = layer;
}

const sf::FloatRect& C_BoxCollider::GetCollidable() {
    SetPosition();
    return AABB;
}

void C_BoxCollider::SetPosition() {
    const sf::Vector2f& pos = owner->transform->GetPosition();

    AABB.left = pos.x - (AABB.width / 2) + offset.x;
    AABB.top = pos.y - (AABB.height / 2) + offset.y;
}

sf::FloatRect C_BoxCollider::GetIntersectionRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    std::vector<float> xs{rect1.left, rect1.left + rect1.width, rect2.left, rect2.left + rect2.width};
    std::vector<float> ys{rect1.top, rect1.top + rect1.height, rect2.top, rect2.top + rect2.height};
    std::sort(xs.begin(), xs.end());
    std::sort(ys.begin(), ys.end());

    return sf::FloatRect(xs[1], ys[1], xs[2] - xs[1], ys[2] - ys[1]);
}
