//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include "SFML/Graphics.hpp"



class Tile;

class Entity {
    //Base class for Enemy, Tile and Player classes
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

    bool isTouchingLeft(const Tile &t) const;   //
    bool isTouchingRight(const Tile &t) const;  //  <-- check if entity is making contact with a tile
    bool isTouchingTop(const Tile &t) const;    //
    bool isTouchingBottom(const Tile &t) const; //
public:
    virtual ~Entity() {
        // std::cout<<"deleted an entity\n";
    };

    void camMoveLeft(float velo);   //
    void camMoveRight(float velo);  //  <-- make sure to keep entities in pplace relative to player
    void camMoveUp(float velo);     //
    void camMoveDown(float velo);   //

    void checkCollision(const Tile& t);
    //Makes sure that if an enemy or player is in contact with a tile, they don`t noclip into it
    friend class Enemy;
    friend class Camera;
};




#endif //OOP_ENTITY_H
