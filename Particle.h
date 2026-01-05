//
// Created by Bogdan on 01-Jan-26.
//

#ifndef OOP_PARTICLE_H
#define OOP_PARTICLE_H

#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

//Flyweight
class Particle {
private:
    sf::Texture m_texture; //<--intrinsic state
public:
    explicit Particle(const std::string &texPath);
    void draw(sf::Vector2f coords /* <--extrinsic state */, sf::RenderWindow& window) const;

    friend class Room;

};


#endif //OOP_PARTICLE_H