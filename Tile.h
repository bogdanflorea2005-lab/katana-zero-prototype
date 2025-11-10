//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_TILE_H
#define OOP_TILE_H
#include "Entity.h"


class Tile: public Entity{
private:

public:
    Tile(const std::string filePath, float x, float y);

    Tile(const Tile& t);

    Tile(const Tile& t, float x, float y);

    void drawTile(sf::RenderWindow& window);

    friend class Entity;
};


#endif //OOP_TILE_H