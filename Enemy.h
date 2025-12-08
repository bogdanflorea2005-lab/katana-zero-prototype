//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include <iostream>

#include "Entity.h"
#include "SFML/Graphics.hpp"


class Camera;
class Player;

class Enemy: public Entity {
private:
    bool isDead=false;


    void moveLeft() override;
    void moveRight() override;
    void gravity() override;
    void stopMovement() override;


public:
    Enemy()=default;
    ~Enemy() {
        // std::cout<<"deleted an enemy\n";
    }

    Enemy(const std::string &filePath, float x, float y);

    void seekPlayer(sf::Vector2f playerCoords); //<-- update() for Observer pattern

    void drawEnemy(sf::RenderWindow &window);

    friend void drawRoom(sf::RenderWindow& window, Player& p, Camera& c, Tile tiles[], int& tileNum, Enemy enemies[], int& enemyNum);


    Enemy &operator=(Enemy* enemy);

    friend class Room;
    friend class Player;

};


#endif //OOP_ENEMY_H