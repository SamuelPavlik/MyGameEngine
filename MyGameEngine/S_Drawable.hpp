#ifndef S_Drawable_hpp
#define S_Drawable_hpp

#include "C_Drawable.hpp"
#include "Object.hpp"

#include <set>
#include <functional>

class S_Drawable {
public:
    S_Drawable();

    void Add(std::vector<std::shared_ptr<Object>>& object);

    void ProcessRemovals();

    void Draw(Window& window);

private:
    void Add(std::shared_ptr<Object> object);

    std::multiset<std::shared_ptr<Object>, std::function<bool(std::shared_ptr<Object>, std::shared_ptr<Object>)>> drawables;

};

#endif /* S_Drawable_hpp */