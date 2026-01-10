//
// Created by Bogdan on 11/7/2025.
//

#include "../Headers/Entity.h"
#include "../Headers/Tile.h"

void Entity::moveLeft() {}

void Entity::moveRight() {}

void Entity::jump() {}

void Entity::gravity() {}

void Entity::stopMovement() {}

void Entity::camMoveLeft(float velo) {
    position.x-=velo;
}

void Entity::camMoveRight(float velo) {
    position.x-=velo;
}

void Entity::camMoveUp(float velo) {
    position.y-=velo;
}

void Entity::camMoveDown(float velo) {
    position.y-=velo;
}

void Entity::attack() {
    //will add sth once I make a "Projectile class"
}

bool Entity::isTouchingLeft(const Tile &t) const {
    if (velocity.x>0) {
        if (position.x+texSize.x/2+velocity.x>t.position.x-t.texSize.x/2 && position.x<t.position.x-t.texSize.x/2 && (position.y>t.position.y-t.texSize.y/2 && position.y-texSize.y/2<t.position.y+t.texSize.y/2)) {
            return true;
        }
    }
    return false;
}

bool Entity::isTouchingRight(const Tile &t) const {
    if (velocity.x<0) {
        if (position.x-texSize.x/2+velocity.x<t.position.x+t.texSize.x/2 && position.x>t.position.x+t.texSize.x/2 && (position.y>t.position.y-t.texSize.y/2 && position.y-texSize.y/2<t.position.y+t.texSize.y/2)) {
            return true;
        }
    }
    return false;
}

bool Entity::isTouchingTop(const Tile &t) const {
    if (velocity.y<0) {
        if (position.y>t.position.y+t.texSize.y/2 && position.y-texSize.y/2+velocity.y<t.position.y+t.texSize.y/2 && (position.x+texSize.x/2>t.position.x-t.texSize.x/2 && position.x-texSize.x/2<t.position.x+t.texSize.x/2)) {
            return true;
        }
    }
    return false;
}

bool Entity::isTouchingBottom(const Tile &t) const {
    if (velocity.y>=0) {
        if (position.y+texSize.y/2+velocity.y>t.position.y-t.texSize.y/2 && position.y<t.position.y-t.texSize.y/2
            && (position.x+texSize.x/2>t.position.x-t.texSize.x/2 && position.x-texSize.x/2<t.position.x+t.texSize.x/2)){
            return true;
        }
    }
    return false;
}

void Entity::checkCollision(const Tile& t) {
    if(position.y>t.position.y-t.texSize.y/2 && position.y-texSize.y/2<t.position.y+t.texSize.y/2) {
        if (isTouchingLeft(t)) {
            position=sf::Vector2f(t.position.x-t.texSize.x/2-texSize.x/2, position.y);
            velocity=sf::Vector2f(0, velocity.y);
        }
        if (isTouchingRight(t)) {
            position=sf::Vector2f(t.position.x+t.texSize.x/2+texSize.x/2, position.y);
            velocity=sf::Vector2f(0, velocity.y);
        }
    }

    if(position.x+texSize.x/2>t.position.x-t.texSize.x/2 && position.x-texSize.x/2<t.position.x+t.texSize.x/2
        && position.y+texSize.y/2>=t.position.y-t.texSize.y/2-texSize.y/2+0.01
        && t.position.y-t.texSize.y-texSize.y<=position.y-texSize.y/2) {
        if (isTouchingBottom(t)) {
        position=sf::Vector2f(position.x, t.position.y-t.texSize.y/2-texSize.y/2+0.01);
        velocity=sf::Vector2f(velocity.x, 0);
        isGrounded=true;
        }else {
            isGrounded=false;
        }
        // std::cout<<"isGrounded: "<<isGrounded<<std::endl<<"yVelo: "<<velocity.y<<std::endl<<"tileID: "<<t.tileID<<std::endl<<std::endl;
        // std::cout<<"isTB: "<<isTouchingBottom(t)<<std::endl;

        if (isTouchingTop(t)) {
            position=sf::Vector2f(position.x, t.position.y+t.texSize.y/2+texSize.y/2);
            velocity=sf::Vector2f(velocity.x, 0.01);
        }
    }
}
