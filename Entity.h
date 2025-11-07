//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class Entity {
protected:
    int direction=0;
    sf::Vector2f position;
    bool isGrounded=false, isDead=false;
    sf::Texture texture;
    sf::Vector2u texSize;
    sf::Vector2f velocity=sf::Vector2f(0, 0);

    void moveLeft();

    void moveRight();

    void jump();

    void gravity();

    void stopMovement();

    void attack();
};




#endif //OOP_ENTITY_H
