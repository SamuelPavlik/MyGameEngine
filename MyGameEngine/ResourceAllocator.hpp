#ifndef ResourceAllocator_hpp
#define ResourceAllocator_hpp

#include <unordered_map>
#include <memory>
#include <string>
#include <algorithm>

template<typename T>
class ResourceAllocator {

public:
    template<typename... Args>
    int Add(const std::string& filePath, const Args&&... args) {
        auto it = std::find_if(resources.cbegin(), resources.cend(), 
            [filePath](std::pair<int, std::pair<std::string, std::shared_ptr<T>>> elem) { 
                return elem.second.first == filePath;
            });

        if (it != resources.end()) {
            return it->first;
        }

        std::shared_ptr<T> resource = std::make_shared<T>(args...);
        //TODO
        //std::shared_ptr<T> resource = std::make_shared<T>(filePath, args...);
        //if (!resource) {
        if (!resource->loadFromFile(filePath)) {
            return -1;
        }

        resources.insert(
            std::make_pair(currentId, std::make_pair(filePath, resource)));

        return currentId++;
    }

    void Remove(int id) {
        resources.erase(id);
    }

    std::shared_ptr<T> Get(int id) {
        if (resources.find(id) != resources.cend())
            return resources[id].second;
        
        return nullptr;
    }

    bool Has(int id) {
        return (Get(id) != nullptr);
    }

private:
    int currentId;
    std::unordered_map<int, std::pair<std::string, std::shared_ptr<T>>> resources;
};

#endif /* ResourceAllocator_hpp */
