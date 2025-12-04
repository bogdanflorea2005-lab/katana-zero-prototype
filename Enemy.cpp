//
// Created by Bogdan on 11/7/2025.
//

#include "Enemy.h"

#include "Player.h"

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

Enemy::Enemy(const std::string &filePath, float x, float y)  {
    if (!texture.loadFromFile(filePath)) {
        std::cout<<"Texture loading failed\n";
        texture.loadFromFile("Textures/Lbozo.png");
    }
    texSize=texture.getSize();
    position.x=x;
    position.y=y;
}

void Enemy::camMoveLeft(float velo) {
    position.x-=velo;
}

void Enemy::camMoveRight(float velo) {
    position.x-=velo;
}

void Enemy::camMoveUp(float velo) {
    position.y-=velo;
}

void Enemy::camMoveDown(float velo) {
    position.y-=velo;
}

void Enemy::drawEnemy(sf::RenderWindow &window) {
    sf::Sprite sprite(texture);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(texSize.x/2,texSize.y/2));
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(1, 1));
    window.draw(sprite);
}

void Enemy::seekPlayer(Player& p) {
    gravity();
    float distance;
    distance = abs(p.position.x - this->position.x);
    if (position.x<p.position.x && distance >30) {
        moveLeft();
    }else if (position.x>p.position.x && distance >30) {
        moveRight();
    }

    if (distance<40 && abs(position.y-p.position.y)<40) {
        p.isDead = true;
    }
}

Enemy & Enemy::operator=(Enemy *enemy) {
    this->position=sf::Vector2f(enemy->position.x, enemy->position.y);
    this->texture=enemy->texture;
    return *this;
}

