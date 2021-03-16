#ifndef C_Transform_hpp
#define C_Transform_hpp

#include "Component.hpp"

class C_Transform : public Component {
public:
    C_Transform(Object* owner);
    C_Transform(Object* owner, bool isStaticTransform);

    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f& pos);
    void SetStatic(bool isStatic);

    void AddPosition(float x, float y);
    void AddPosition(const sf::Vector2f& pos);

    // Allows us to set x/y values separately.
    void SetX(float x);
    void SetY(float y);
    void AddX(float x);
    void AddY(float y);

    bool IsStatic() const;
    const sf::Vector2f& GetPosition() const;

private:
    sf::Vector2f position;
    bool isStaticTransform;
};

#endif /* C_Transform_hpp */