//
// Created by Bogdan on 12/1/2025.
//

#ifndef OOP_ROOM_H
#define OOP_ROOM_H
#include <string>

#include "Tile.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"


class Room {
private:
    std::string roomID;
    int tileNum, enemyNum;
    sf::Vector2f checkpointPos;
    Tile tiles[5];
    Enemy enemies[2];

    bool hasError=0;

public:
    Room(std::string roomID);
    ~Room() {
        std::cout<<"deleted a room\n";
    }

    void drawRoom(sf::RenderWindow& window, Player& p, Camera& c);
};


#endif //OOP_ROOM_H