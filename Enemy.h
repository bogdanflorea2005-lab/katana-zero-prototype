//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include "Entity.h"
#include "SFML/Graphics.hpp"


class Enemy: public Entity {
private:

public:
    Enemy(const std::string &filePath, float x, float y) {
        texture.loadFromFile(filePath);
        texSize=texture.getSize();
        position.x=x;
        position.y=y;
    }

    void drawEnemy(sf::RenderWindow &window);


};


#endif //OOP_ENEMY_H