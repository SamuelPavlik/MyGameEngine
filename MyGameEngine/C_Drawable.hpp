#ifndef C_Drawable_hpp
#define C_Drawable_hpp

#include "Window.hpp"

#include <SFML/Graphics.hpp>

class Windows;

enum class DrawLayer {
    Default,
    Background,
    Foreground,
    Entities
};

class C_Drawable {
public:
    C_Drawable();
    virtual ~C_Drawable();

    virtual void Draw(Window& window) = 0;

    void SetSortOrder(int order);
    int GetSortOrder() const;

    void SetDrawLayer(DrawLayer layer);
    DrawLayer GetDrawLayer() const;

    virtual bool IsQueuedForRemoval() const = 0;

private:
    int sortOrder;
    DrawLayer layer;
};

#endif /* C_Drawable_hpp */