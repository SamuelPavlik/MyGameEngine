#ifndef TileMapParser_hpp
#define TileMapParser_hpp

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <sstream>
#include <memory>

struct Tile;
struct TileInfo;
class Object;
template<typename T>
class ResourceAllocator;

using namespace rapidxml;
using Layer = std::vector<std::shared_ptr<Tile>>;
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>;
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;

struct TileSheetData {
    // The texture id will be retrieved by using our texture allocator.
    int textureId; // The id of the tile sets texture. 
    sf::Vector2u imageSize; // The size of the texture.
    int columns; // How many columns in the tile sheet.
    int rows; // How many rows in the tile sheet.
    sf::Vector2u tileSize; // The size of an individual tile.
};

class TileMapParser {
public:
    TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator);

    std::vector<std::shared_ptr<Object>> Parse(const std::string& file, sf::Vector2i offset);

private:
    std::shared_ptr<TileSheetData> BuildTileSheetData(xml_node<>* rootNode);

    std::shared_ptr<MapTiles> BuildMapTiles(xml_node<>* rootNode);

    std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(
        xml_node<>* layerNode, std::shared_ptr<TileSheetData> tileSheetData);

    ResourceAllocator<sf::Texture>& textureAllocator;
};

#endif /* TileMapParser_hpp */