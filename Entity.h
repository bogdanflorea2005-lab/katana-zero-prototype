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
    bool isGrounded=false;
    sf::Texture texture;
    sf::Vector2u texSize;
    sf::Vector2f velocity=sf::Vector2f(0, 0);

    virtual void moveLeft(); //

    virtual void moveRight(); //

    virtual void jump(); //

    virtual void gravity(); //

    virtual void stopMovement(); //

    virtual void attack();

    bool isTouchingLeft(Tile t) const;
    bool isTouchingRight(Tile t) const;
    bool isTouchingTop(Tile t) const;
    bool isTouchingBottom(Tile t) const;
public:
    virtual ~Entity() {
        // std::cout<<"deleted an entity\n";
    };

    void camMoveLeft(float velo);
    void camMoveRight(float velo);
    void camMoveUp(float velo);
    void camMoveDown(float velo);

    void checkCollision(Tile& t);
    friend class Enemy;
    friend class Camera;
};




#endif //OOP_ENTITY_H
