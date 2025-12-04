//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <iostream>

#include "Entity.h"
#include "SFML/Graphics.hpp"


class Player: public Entity {
private:
    int spaceTimer=0;

    void moveLeft() override;
    void moveRight() override;
    void gravity() override;
    void stopMovement() override;
    void jump() override;

    void setPosition(sf::Vector2f pos) {
        position.x=pos.x;
        position.y=pos.y;
    }

public:
    Player(const std::string &filePath, float x, float y);
    ~Player() {
        std::cout<<"deleted player\n";
    };

    bool getDead() {
        return isDead;
    }

    void drawPlayer(sf::RenderWindow& window);

    void movement();

    Player &operator=(Player * player);

    friend class Enemy;
    friend class Camera;
    friend class Room;
};


#endif //OOP_PLAYER_H