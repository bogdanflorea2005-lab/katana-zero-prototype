//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_TILE_H
#define OOP_TILE_H

#include "Entity.h"
#include "Camera.h"


class Player;

class Tile: public Entity{
private:
    int tileID=0;



public:

    Tile &operator=(const Tile * tile);

    Tile()=default;

    Tile(const std::string& filePath, float x, float y, int tileID);

    Tile(const Tile& t);

    Tile(const Tile& t, float x, float y, int tileID);

    void drawTile(sf::RenderWindow& window) const;


    friend std::ostream& operator<<(std::ostream& os, const Tile& t) {
        os << t.tileID<<"\n";
        os << "x: "<<t.position.x << " y: "<<t.position.y<<"\n";
        return os;

    }

    friend void drawRoom(sf::RenderWindow& window, Player& p, Camera& c, Tile tiles[], int& tileNum, Enemy enemies[], int& enemyNum);


    friend class Entity;
    friend class Room;
    friend class Camera;
};


#endif //OOP_TILE_H