//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_TILE_H
#define OOP_TILE_H
#include <iostream>

#include "Entity.h"


class Tile: public Entity{
private:
    int tileID=0;

public:
    void moveLeft(float velo);
    void moveRight(float velo);
    void moveUp(float velo);
    void moveDown(float velo);

    Tile &operator=(Tile * tile);

    Tile()=default;

    ~Tile() {
        std::cout<<"deleted a tile\n";
    };

    Tile(const std::string filePath, float x, float y, int tileID);

    Tile(const Tile& t);

    Tile(const Tile& t, float x, float y, int tileID);

    void drawTile(sf::RenderWindow& window);


    friend std::ostream& operator<<(std::ostream& os, const Tile& t) {
        os << t.tileID<<"\n";
        os << "x: "<<t.position.x << " y: "<<t.position.y<<"\n";
        return os;

    }

    friend class Entity;
    friend class Camera;
};


#endif //OOP_TILE_H