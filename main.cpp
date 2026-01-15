#include <iostream>

#include <SFML/Graphics.hpp>


#include "Headers/Camera.h"

#include "Headers/Player.h"
#include "Headers/Room.h"

#include "Headers/TextureLoadingException.h"


template <typename T1> void freeTempFunc(T1& a, T1& b) {
    std::cout<<"template func outside of template class\n";
    if (a<b) {
        a+=b;
    }else {
        b+=a;
    }

}

int Player::enemiesKilled=0;

void displayImage(sf::RenderWindow& w, const std::string& imagePath) {
    sf::Texture texture;
    try {
        if (!texture.loadFromFile(imagePath)) {
            throw TextureLoadingException(imagePath);
        }
    }catch (TextureLoadingException texEx) {
        try {
            if (!texture.loadFromFile("Textures/Lbozo.png")) {
                throw TextureLoadingException("Textures/Lbozo.png");
            }

        }catch ([[maybe_unused]] TextureLoadingException& severeTexErr) {
            std::cerr<<"error image has an error :/\n";
        }
    }

    sf::Sprite sprite(texture);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x/2, texture.getSize().y/2));
    sprite.setPosition(sf::Vector2f(w.getSize().x / 2, w.getSize().y / 2));
    sprite.setScale(sf::Vector2f(10, 10));
    w.draw(sprite);
}

int main() {

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    const std::string filePath1="Textures/placeholder.png";
    Player p(filePath1, window.getSize().x/2, window.getSize().y/2);
    Camera c(sf::Vector2f(window.getSize().x, window.getSize().y));

    Room room("test", window);

    room.drawRoom(window, p, c);

    return 0;
}


