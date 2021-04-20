#ifndef TileMapParser_hpp
#define TileMapParser_hpp

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

struct Tile;
struct TileInfo;
class Object;
template<typename T>
class ResourceAllocator;

struct Layer {
    std::vector<std::shared_ptr<Tile>> tiles;
    bool isVisible;
    int sortOrder;
};

using namespace rapidxml;
using LayerMap = std::unordered_map<std::string, std::shared_ptr<Layer>>;
using TileSetMap = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;

struct TileSetData {
    int textureId;
    sf::Vector2u imageSize;
    int columns;
    int rows;
    sf::Vector2u tileSize;
};
using TileSets = std::map<int, std::shared_ptr<TileSetData>>;

class TileMapParser {
public:
    TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator);

    std::vector<std::shared_ptr<Object>> Parse(const std::string& file, sf::Vector2i offset);

private:
    std::shared_ptr<TileSets> BuildTileSets(xml_node<>* rootNode);
    std::shared_ptr<LayerMap> BuildLayerMap(xml_node<>* rootNode);
    std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(
        xml_node<>* layerNode, std::shared_ptr<TileSets> tileSets);


    ResourceAllocator<sf::Texture>& textureAllocator;
};

#endif /* TileMapParser_hpp */