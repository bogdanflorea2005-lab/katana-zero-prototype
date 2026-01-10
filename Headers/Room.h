//
// Created by Bogdan on 12/1/2025.
//

#ifndef OOP_ROOM_H
#define OOP_ROOM_H
#include <string>
#include <array>

#include "Tile.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"


class Room {
private:
    std::string roomID;
    int tileStartPos, tileEndPos, enemyStartPos, enemyEndPos, particleNum, entityNum;
    sf::Vector2f checkpointPos, roomSize, roomCentre;

    std::vector<std::shared_ptr<Entity>> entities;
    std::array<std::string, 1> particleKeys;

    bool hasError=false;

public:
    ~Room() {
        std::cout << "Room Destroyed" << std::endl;
    }
    /*
     * Room data is loaded through this constructor.
     */
    explicit Room(const std::string &roomID, sf::RenderWindow &window);

    /*
     * This function displays tiles and enemies.
     */
    void drawRoom(sf::RenderWindow& window, Player& player, Camera& camera);


    friend class RoomIDException;

};


#endif //OOP_ROOM_H