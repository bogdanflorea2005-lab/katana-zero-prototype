//
// Created by Bogdan on 12/1/2025.
//

#ifndef OOP_ROOM_H
#define OOP_ROOM_H
#include <string>

#include "Tile.h"
#include "Enemy.h"


class Room {
private:
    std::string roomID;
    int tileNum, enemyNum;
    sf::Vector2f checkpointPos;
    Tile tiles[100];
    Enemy enemies[100];

public:
    Room(std::string roomID);

    void drawRoom(sf::RenderWindow& window, Player& p, Camera& c);
};


#endif //OOP_ROOM_H