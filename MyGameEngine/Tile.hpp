#ifndef Tile_h
#define Tile_h

#include <SFML/Graphics.hpp>

struct TileInfo {
    TileInfo() : 
        tileID(-1), 
        textureID(-1), 
        textureRect(sf::IntRect(0, 0, 0, 0)) {}

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