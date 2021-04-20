#include "TileMapParser.hpp"
#include "Tile.hpp"
#include "Utilities.hpp"
#include "Object.hpp"
#include "ResourceAllocator.hpp"
#include "C_Sprite.hpp"
#include "C_BoxCollider.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

TileMapParser::TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator)
    : textureAllocator(textureAllocator) {
}

std::vector<std::shared_ptr<Object>> TileMapParser::Parse
    (const std::string& file, sf::Vector2i offset) {

    //TODO: error checking - check file exists before attempting open.
    rapidxml::file<> xmlFile(file.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    auto rootNode = doc.first_node("map");

    // Loads tile layers from XML.
    auto layerMap = BuildLayerMap(rootNode);

    // We need these to calculate the tiles position in world space
    auto tileSizeX = std::atoi(rootNode->first_attribute("tilewidth")->value());
    auto tileSizeY = std::atoi(rootNode->first_attribute("tileheight")->value());
    auto mapsizeX = std::atoi(rootNode->first_attribute("width")->value());
    auto mapsizeY = std::atoi(rootNode->first_attribute("height")->value());

    // This will contain all of our tiles as objects.
    std::vector<std::shared_ptr<Object>> tileObjects;

    // We iterate through each layer in the tile map
    for (const auto& layer : *layerMap) {
        /*if (!layer.second->isVisible)
            continue;*/
        // And each tile in the layer
        for (const auto& tile : layer.second->tiles) {
            auto tileInfo = tile->properties;
            auto tileObject = std::make_shared<Object>();

            //TODO: tile scale should be set at the data level.
            const auto tileScale = 1.5f;

            // Allocate sprite if needed
            if (layer.second->isVisible) {
                auto sprite = tileObject->AddComponent<C_Sprite>(textureAllocator);
                sprite->Load(tileInfo->textureID);
                sprite->SetTextureRect(tileInfo->textureRect);
                sprite->SetScale(tileScale, tileScale);
                sprite->SetSortOrder(layer.second->sortOrder);
                sprite->SetDrawLayer(DrawLayer::Background);
            }
            // Calculate world position.
            auto x = tile->x * tileSizeX * tileScale + offset.x;
            auto y = tile->y * tileSizeY * tileScale + offset.y;
            tileObject->transform->SetPosition(x, y);

            // Set collision component if required
            if (layer.first == "Collisions") {
                auto left = x - (tileSizeX * tileScale) * 0.5f;
                auto top = y - (tileSizeY * tileScale) * 0.5f;
                auto width = tileSizeX * tileScale;
                auto height = tileSizeY * tileScale;
                auto collider = tileObject->AddComponent<C_BoxCollider>(
                    sf::FloatRect(left, top, width, height), CollisionLayer::Tile);
                tileObject->transform->SetStatic(true);
            }

            // Add new tile Object to the collection.
            tileObjects.emplace_back(tileObject);
        }
    }

    return tileObjects;
}

std::shared_ptr<TileSets> TileMapParser::BuildTileSets(xml_node<>* rootNode) {
    TileSets tileSets;

    for (auto tileSetNode = rootNode->first_node("tileset");
        tileSetNode;
        tileSetNode = tileSetNode->next_sibling("tileset")) {

        TileSetData tileSetData;
        //TODO: add error checking to ensure these values actually exist.
        //TODO: add support for multiple tile sets.
        //TODO: implement this.
        auto firstgid = std::atoi(tileSetNode->first_attribute("firstgid")->value());

        // Build the tile sheet data.
        tileSetData.tileSize.x =
            std::atoi(tileSetNode->first_attribute("tilewidth")->value());
        tileSetData.tileSize.y =
            std::atoi(tileSetNode->first_attribute("tileheight")->value());
        auto tileCount =
            std::atoi(tileSetNode->first_attribute("tilecount")->value());
        tileSetData.columns =
            std::atoi(tileSetNode->first_attribute("columns")->value());
        tileSetData.rows = tileCount / tileSetData.columns;

       auto imageNode = tileSetNode->first_node("image");
       tileSetData.textureId =
            textureAllocator.Add(std::string(imageNode->first_attribute("source")->value()));

        //TODO: add error checking - we want to output a 
        //message if the texture is not found.

        tileSetData.imageSize.x =
            std::atoi(imageNode->first_attribute("width")->value());
        tileSetData.imageSize.y =
            std::atoi(imageNode->first_attribute("height")->value());

        tileSets[firstgid] = std::make_shared<TileSetData>(tileSetData);
    }
    return std::make_shared<TileSets>(tileSets);
}

std::shared_ptr<LayerMap> TileMapParser::BuildLayerMap(xml_node<>* rootNode) {
    auto tileSets = BuildTileSets(rootNode);
    std::shared_ptr<LayerMap> map = std::make_shared<LayerMap>();

    auto sortOrder = 0;
    for (xml_node<>* node = rootNode->first_node("layer"); node; node = node->next_sibling()) {
        std::pair<std::string, std::shared_ptr<Layer>> mapLayer =
            BuildLayer(node, tileSets);
        mapLayer.second->sortOrder = sortOrder++;
        map->emplace(mapLayer);
    }

    return map;
}

std::pair<std::string, std::shared_ptr<Layer>> TileMapParser::BuildLayer(
    xml_node<>* layerNode, std::shared_ptr<TileSets> tileSets) {

    TileSetMap tileSetMap;
    auto layer = std::make_shared<Layer>();

    auto width = std::atoi(layerNode->first_attribute("width")->value());
    auto height = std::atoi(layerNode->first_attribute("height")->value());

    auto dataNode = layerNode->first_node("data");
    auto mapIndices = dataNode->value();

    std::stringstream fileStream(mapIndices);

    auto count = 0;

    std::string line;
    while (fileStream.good()) {
        std::string substr;
        std::getline(fileStream, substr, ',');

        if (!Utilities::IsInteger(substr)) {
            // We remove special characters from the int before parsing
            substr.erase(
                std::remove(substr.begin(), substr.end(), '\r'), substr.end());
            substr.erase(
                std::remove(substr.begin(), substr.end(), '\n'), substr.end());

            //TODO: add additional check to 
            //confirm that the character removals have worked:
        }

        auto tileId = std::stoll(substr);

        if (tileId != 0) {
            auto itr = tileSetMap.find(tileId);
            if (itr == tileSetMap.end()) {
                std::shared_ptr<TileSetData> tileSet;

                auto tileSetIter = std::find_if(tileSets->rbegin(), tileSets->rend(), [tileId](const auto& pairElem) {
                    return tileId >= pairElem.first; });
                if (tileSetIter == tileSets->rend()){
                    //TODO: output error message.
                    continue;
                }
                else {
                    tileSet = tileSetIter->second;
                }

                auto textureX = (tileId - tileSetIter->first) % tileSet->columns;
                auto textureY = (tileId - tileSetIter->first) / tileSet->columns;

                auto tileInfo = std::make_shared<TileInfo>(
                        tileSet->textureId, tileId,
                        sf::IntRect(
                            textureX * tileSet->tileSize.x,
                            textureY * tileSet->tileSize.y,
                            tileSet->tileSize.x,
                            tileSet->tileSize.y)
                        );

                itr = tileSetMap.insert(std::make_pair(tileId, tileInfo)).first;
            }

            auto tile = std::make_shared<Tile>();

            // Bind properties of a tile from a set.
            tile->properties = itr->second;
            tile->x = count % width;
            tile->y = count / width;

            layer->tiles.emplace_back(tile);
        }

        count++;
    }

    // set layer visibility
    bool layerVisible = true;
    auto visibleAttribute = layerNode->first_attribute("visible");
    if (visibleAttribute)
        layerVisible = std::stoi(visibleAttribute->value());
    layer->isVisible = layerVisible;

    // set layer name mapping
    const std::string layerName = layerNode->first_attribute("name")->value();

    return std::make_pair(layerName, layer);
}
