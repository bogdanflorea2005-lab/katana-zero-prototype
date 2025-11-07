//
// Created by Bogdan on 11/7/2025.
//

#include "Entity.h"

void Entity::moveLeft() {
    velocity.x += 0.25;
    if (velocity.x>=6) {
        velocity.x = 6;
    }
    position.x+=velocity.x;
}

void Entity::moveRight() {
    velocity.x -= 0.25;
    if (velocity.x<=-6) {
        velocity.x = -6;
    }
    position.x+=velocity.x;
}

void Entity::jump() {
    if (isGrounded==true) {
        isGrounded = false;
        velocity.y=0;
        velocity.y -=15;
        position.y+=velocity.y;
    }
}

void Entity::gravity() {
    velocity.y+=0.25;
    if (velocity.y>=5) {
        velocity.y = 5;
    }
    position.y+=velocity.y;
}

void Entity::stopMovement() {
    direction=velocity.x/abs(velocity.x);
    if (abs(velocity.x)>0) {
        velocity.x -= 0.25*direction;
    }
    position.x+=velocity.x;
}

void Entity::attack() {
    //will add sth once I make a "Projectile class"
}
