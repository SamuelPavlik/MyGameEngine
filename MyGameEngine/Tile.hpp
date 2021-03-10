#ifndef Tile_h
#define Tile_h

#include "ResourceAllocator.hpp"
#include <SFML/Graphics.hpp>

struct TileInfo {
    TileInfo() : tileID(-1) {}

    TileInfo(int textureID, long long tileID, sf::IntRect textureRect)
        : textureID(textureID), tileID(tileID), textureRect(textureRect) {}

    long long tileID;
    int textureID;
    sf::IntRect textureRect;
};

struct Tile {
    std::shared_ptr<TileInfo> properties;
    int x;
    int y;
};

#endif /* Tile_h */