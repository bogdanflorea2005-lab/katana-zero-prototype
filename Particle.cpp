//
// Created by Bogdan on 01-Jan-26.
//

#include "Particle.h"
#include <iostream>

#include "TextureLoadingException.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"

Particle::Particle(const std::string &texPath) {
    try {
        if (!m_texture.loadFromFile(texPath)) {
            TextureLoadingException ex(texPath);
            throw ex;
        }
    }catch (TextureLoadingException ex) {
        try {
            if (!m_texture.loadFromFile("Textures/errorImg.png")) {
                TextureLoadingException ex2("Textures/errorImg.png");
                throw ex2;
            }
        }catch (TextureLoadingException ex2) {
            std::cerr<<"\n\nError loading error image\n\n";
        }
    }
}

void Particle::draw(const sf::Vector2f coords, sf::RenderWindow& window) const {
    sf::Sprite sprite(m_texture);
    sprite.setPosition(coords);
    window.draw(sprite);
}
