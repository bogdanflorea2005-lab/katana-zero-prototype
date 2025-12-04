//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H
#include <iostream>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class Tile;

class Entity {
protected:
    int direction=0, airTime=0;
    sf::Vector2f position;
    bool isGrounded=false, isDead=false;
    sf::Texture texture;
    sf::Vector2u texSize;
    sf::Vector2f velocity=sf::Vector2f(0, 0);

    virtual void moveLeft(); //

    virtual void moveRight(); //

    virtual void jump(); //

    virtual void gravity(); //

    virtual void stopMovement(); //

    virtual void attack();

    bool isTouchingLeft(Tile t);
    bool isTouchingRight(Tile t);
    bool isTouchingTop(Tile t);
    bool isTouchingBottom(Tile t);
public:
    virtual ~Entity() {
        std::cout<<"deleted an entity\n";
    };


    void checkCollision(Tile& t);
    friend class Enemy;
    friend class Camera;
};




#endif //OOP_ENTITY_H
