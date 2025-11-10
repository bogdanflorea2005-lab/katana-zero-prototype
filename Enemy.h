//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include "Entity.h"
#include "SFML/Graphics.hpp"


class Player;

class Enemy: public Entity {
private:

public:
    Enemy(const std::string &filePath, float x, float y);

    void drawEnemy(sf::RenderWindow &window);

    void seekPlayer(Player& p);


};


#endif //OOP_ENEMY_H