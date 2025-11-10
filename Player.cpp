//
// Created by Bogdan on 11/7/2025.
//

#include "Player.h"

Player::Player(const std::string &filePath, float x, float y) {
    texture.loadFromFile(filePath);
    texSize=texture.getSize();
    position.x=x;
    position.y=y;
}

void Player::drawPlayer(sf::RenderWindow &window) {
    sf::Sprite sprite(texture);
    sprite.setOrigin(sf::Vector2f(texSize.x/2,texSize.y/2));
    sprite.setPosition(sf::Vector2f(position.x,position.y));
    sprite.setScale(sf::Vector2f(1, 1));
    window.draw(sprite);
}

void Player::movement() {
    gravity();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)==0) {
        moveRight();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)==0) {
        moveLeft();
    }else {
        stopMovement();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)==1 && isGrounded==true) {
        jump();
    }
}




