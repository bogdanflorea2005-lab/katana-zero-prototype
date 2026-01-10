//
// Created by Bogdan on 11/17/2025.
//

#include "../Headers/Camera.h"

#include <iostream>

#include "../Headers/Enemy.h"
#include "../Headers/Player.h"

Camera::Camera(sf::Vector2f origin) {
    this->origin=origin;
}

/*void Camera::drawCambox(sf::RenderWindow &window, const std::string texFile) {
    sf::Texture texture;
    texture.loadFromFile(texFile);
    sf::Sprite sprite(texture);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x/2, texture.getSize().y/2));
    sprite.setPosition(sf::Vector2f(960, 540));
    //sprite.setScale(sf::Vector2f(1, 1));
    window.draw(sprite);
    //std::cout<<"x: "<<origin.x<<"y: "<<origin.y<<std::endl;
}*/

void Camera::setOrigin(const sf::Vector2f &v) {
    origin=v;
}

bool Camera::isTouchingUpper(const Player &p) const {
    if (p.velocity.y<0) {
        if (p.position.y-p.texSize.y/2+p.velocity.y<origin.y-size.y/2) {
            return true;
        }
    }
    return false;
}

bool Camera::isTouchingLower(const Player &p) const {
    if (p.velocity.y>0) {
        if (p.position.y+p.texSize.y/2+p.velocity.y>origin.y+size.y/2) {
            return true;
        }
    }
    return false;
}

bool Camera::isTouchingLeft(const Player &p) const {
    if (p.velocity.x<0) {
        if (p.position.x-p.texSize.x/2+p.velocity.x<origin.x-size.x/2) {
            return true;
        }
    }
    return false;
}

bool Camera::isTouchingRight(const Player &p) const {
    if (p.velocity.x>0) {
        if (p.position.x+p.texSize.x/2+p.velocity.x>origin.x+size.x/2) {
            return true;
        }
    }
    return false;
}

bool Camera::isXCentered(const Player &p) const {
    if (p.position.x!=origin.x) {
        return false;
    }
    return true;
}

bool Camera::isYCentered(const Player &p) const {
    if (p.position.y!=origin.y) {
        return false;
    }
    return true;
}

void Camera::playerReachedBoundary(Player &p, Entity &e) const {
    //This function makes sure that the player stays within the camera boundary
    if (isTouchingUpper(p)) {
        e.camMoveUp(p.velocity.y);
        p.position.y=origin.y-size.y/2+p.texSize.y/2;
    }
    if (isTouchingLower(p)) {
        e.camMoveDown(p.velocity.y);
        p.position.y=origin.y+size.y/2-p.texSize.y/2;
    }
    if (isTouchingLeft(p)) {
        e.camMoveLeft(p.velocity.x);
        p.position.x=origin.x-size.x/2+p.texSize.x/2;
    }
    if (isTouchingRight(p)) {
        e.camMoveRight(p.velocity.x);
        p.position.x=origin.x+size.x/2-p.texSize.x/2;
    }
}

void Camera::moveEntityWhenCentering(const Player &p, Entity& e) const {
    //moves entities in order to keep their position relative to the player the same
    sf::Vector2f distance=sf::Vector2f(abs(p.position.x-origin.x), abs(p.position.y-origin.y));
    if (p.velocity.x==0 && !isXCentered(p)) {
        e.position.x-=(distance.x/110)*((p.position.x-origin.x)/abs((p.position.x-origin.x)));
    }
    if ((p.velocity.y>-2 && p.velocity.y<2) && !isYCentered(p) && p.isGrounded==true) {
        e.position.y-=(distance.y/110)*((p.position.y-origin.y)/abs((p.position.y-origin.y)));
    }
}



void Camera::centerPlayer(Player &p) const {
    //centers the player to the center of the screen
    sf::Vector2f distance=sf::Vector2f(abs(p.position.x-origin.x), abs(p.position.y-origin.y));
    if (p.velocity.x==0 && !isXCentered(p)) {
        p.position.x-=(distance.x/110)*((p.position.x-origin.x)/abs((p.position.x-origin.x)));
    }

    // std::cout<<"inCamera/centerPlayer\nisYCentered: "<<isYCentered(p)<<std::endl<<"yVelo: "<<(p.velocity.y>-2 && p.velocity.y<2)<<"\n";
    // std::cout<<"\nif: "<<((p.velocity.y>-2 && p.velocity.y<2) && !isYCentered(p))<<"\n";
    if ((p.velocity.y>-2 && p.velocity.y<2) && !isYCentered(p)) {
        p.position.y-=(distance.y/110)*((p.position.y-origin.y)/abs((p.position.y-origin.y)));
    }
}
