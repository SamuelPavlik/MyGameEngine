#ifndef S_Drawable_hpp
#define S_Drawable_hpp

#include "C_Drawable.hpp"

#include <map>

class Object;

using Layers = std::vector<std::shared_ptr<C_Drawable>>;
using DrawablesMap = std::map<DrawLayer, Layers>;

class S_Drawable {
public:
    S_Drawable();

    void Add(std::vector<std::shared_ptr<Object>>& object);
    void ProcessRemovals();
    void Draw(Window& window);

private:
    void Add(std::shared_ptr<Object>& object);
    void Sort();

    DrawablesMap drawablesMap;
};

#endif /* S_Drawable_hpp */