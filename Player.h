//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <iostream>

#include "Entity.h"
#include "Camera.h"
#include "Enemy.h"
#include "Tile.h"
#include "SFML/Graphics.hpp"


class Player: public Entity {
public:
    static int enemiesKilled;
private:
    int spaceTimer=0;
    std::string currentRoom;
    sf::Vector2f coordinates;

    void moveLeft() override;
    void moveRight() override;
    void gravity() override;
    void stopMovement() override;
    void jump() override;

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();

    void setCurrentRoom(const std::string& roomID);
    std::string getCurrentRoom();

public:
    Player(const std::string &filePath, float x, float y);
    ~Player() {
        std::cout<<"enemies killed: "<<enemiesKilled<<std::endl;
        std::cout<<"deleted player\n";
    };

    bool getDead() {
        return isDead;
    }

    void drawPlayer(sf::RenderWindow& window);

    void movement();

    Player &operator=(Player * player);

    static void tempAttack(Enemy& e);

    friend void drawRoom(sf::RenderWindow& window, Player& p, Camera& c, Tile tiles[], int& tileNum, Enemy enemies[], int& enemyNum);

    friend class Enemy;
    friend class Camera;
    friend class Room;
};


#endif //OOP_PLAYER_H