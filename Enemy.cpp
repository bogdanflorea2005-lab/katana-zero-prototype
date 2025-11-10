//
// Created by Bogdan on 11/7/2025.
//

#include "Enemy.h"

#include "Player.h"

Enemy::Enemy(const std::string &filePath, float x, float y)  {
    texture.loadFromFile(filePath);
    texSize=texture.getSize();
    position.x=x;
    position.y=y;
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

