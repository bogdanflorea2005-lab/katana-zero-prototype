//
// Created by Bogdan on 11/7/2025.
//

#include "Player.h"

#include <iostream>

#include "TextureLoadingError.h"

void Player::setPosition(sf::Vector2f pos) {
    position.x=pos.x;
    position.y=pos.y;
}

sf::Vector2f Player::getPosition() {
    return sf::Vector2f(position.x, position.y);
}

sf::Vector2f Player::getVelocity() {
    // std::cout<<"X: "<<velocity.x<<std::endl;
    // std::cout<<"Y: "<<velocity.y<<std::endl;
    return sf::Vector2f(velocity.x, velocity.y);
}

void Player::setCurrentRoom(const std::string& roomID) {
    currentRoom=roomID;
}

std::string Player::getCurrentRoom() {
    return currentRoom;
}

void Player::moveLeft() {
    velocity.x += 0.25;
    if (velocity.x>=6) {
        velocity.x = 6;
    }
    position.x+=velocity.x;
}

void Player::moveRight() {
    velocity.x -= 0.25;
    if (velocity.x<=-6) {
        velocity.x = -6;
    }
    position.x+=velocity.x;
}

void Player::gravity() {
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

void Player::stopMovement() {
    direction=velocity.x/abs(velocity.x);
    if (abs(velocity.x)>0) {
        velocity.x -= 0.25*direction;
    }
    position.x+=velocity.x;
}

void Player::jump() {
    isGrounded=false;
    velocity.y-=1.9;
}

Player::Player(const std::string &filePath, float x, float y) {
    // std::cout<<"creating a player\n\n";
    try {

        if (!texture.loadFromFile(filePath)) {
            throw TextureLoadingError(filePath);
        }
        texSize=texture.getSize();
        position.x=x;
        position.y=y;

    }catch (TextureLoadingError texErr) {
        try {

            if (!texture.loadFromFile("Textures/Lbozo.png")) {
                throw TextureLoadingError("Textures/Lbozo.png");
            }
            texSize=texture.getSize();
            position.x=x;
            position.y=y;

        }catch (TextureLoadingError severeTexErr) {
            std::cerr<<"error image has an error :/\n";
        }
    }

}

void Player::drawPlayer(sf::RenderWindow &window) {
    sf::Sprite sprite(texture);
    sprite.setOrigin(sf::Vector2f(texSize.x/2,texSize.y/2));
    sprite.setPosition(sf::Vector2f(position.x,position.y));
    sprite.setScale(sf::Vector2f(1, 1));
    window.draw(sprite);
}

void Player::movement() {

    //std::cout<<"in Player.cpp/movement()\nyVelo: "<<velocity.y<<"\nisGrounded: "<<isGrounded<<std::endl;
    gravity();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)==0) {
        moveRight();
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)==0) {
        moveLeft();
    }else {
        //stopMovement();
        velocity.x=0;
    }
    if (isGrounded) {
        spaceTimer=0;
    }else {

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)==1 && (isGrounded==true || velocity.y<=0) && spaceTimer<15) {
        jump();
        spaceTimer++;
    }


}

Player & Player::operator=(Player *player) {
    position.x=player->position.x;
    position.y=player->position.y;
    isGrounded=player->isGrounded;

    return *this;
}

void Player::tempAttack(Enemy &e) {
    //temporary attack to check if static enemy kill counter works
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)==1 && !e.isDead) {
        enemiesKilled++;
        e.isDead=true;
    }
}
