//
// Created by Bogdan on 11/7/2025.
//

#include "Enemy.h"

void Enemy::drawEnemy(sf::RenderWindow &window) {
    sf::Sprite sprite(texture);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(texSize.x/2,texSize.y/2));
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(1, 1));
    window.draw(sprite);
}

