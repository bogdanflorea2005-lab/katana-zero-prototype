//
// Created by Bogdan on 11/7/2025.
//

#include "Enemy.h"

#include "Player.h"
#include "TextureLoadingException.h"



void Enemy::moveLeft() {
    velocity.x += 0.25;
    if (velocity.x>=6) {
        velocity.x = 6;
    }
    position.x+=velocity.x;
}

void Enemy::moveRight() {
    velocity.x -= 0.25;
    if (velocity.x<=-6) {
        velocity.x = -6;
    }
    position.x+=velocity.x;
}

void Enemy::gravity() {
    if (isGrounded) {
        airTime=0;
    }
    airTime++;
    velocity.y+=0.5;
    if (velocity.y>=9) {
        velocity.y = 9;
    }
    position.y+=velocity.y;
}

void Enemy::stopMovement() {
    direction=velocity.x/abs(velocity.x);
    if (abs(velocity.x)>0) {
        velocity.x -= 0.25*direction;
    }
    position.x+=velocity.x;
}

Enemy::Enemy(const std::string &filePath, float x, float y): Entity()  {
    // std::cout<<"creating an enemy\n\n";
    try {

        if (!texture.loadFromFile(filePath)) {
            throw TextureLoadingException(filePath);
        }
        texSize=texture.getSize();
        position.x=x;
        position.y=y;

    }catch (TextureLoadingException texErr) {
        try {
            if (!texture.loadFromFile("Textures/Lbozo.png")) {
                throw TextureLoadingException("Textures/Lbozo.png");
            }
            texSize=texture.getSize();
            position.x=x;
            position.y=y;
        }catch (TextureLoadingException severeTexErr) {
            std::cerr<<"error image has an error :/\n";

        }
    }
}

void Enemy::seekPlayer(sf::Vector2f playerCoords) {
    if (!isDead) {
        gravity();
        if (const float distance = abs(playerCoords.x - this->position.x); position.x<playerCoords.x && distance >30) {
            moveLeft();
        }else if (position.x>playerCoords.x && distance >30) {
            moveRight();
        }
    }

}

void Enemy::drawEnemy(sf::RenderWindow &window) const {
    if (!isDead) {
        sf::Sprite sprite(texture);
        sprite.setTexture(texture);
        sprite.setOrigin(sf::Vector2f(texSize.x/2,texSize.y/2));
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(1, 1));
        window.draw(sprite);
    }
}

Enemy & Enemy::operator=(const Enemy *enemy) {
    this->position=sf::Vector2f(enemy->position.x, enemy->position.y);
    this->texture=enemy->texture;
    return *this;
}

