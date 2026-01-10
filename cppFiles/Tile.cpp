//
// Created by Bogdan on 11/7/2025.
//

#include "../Headers/Tile.h"

#include "../Headers/TextureLoadingException.h"

class TextureLoadingException;

Tile &Tile::operator=(const Tile *tile) {
    this->position=sf::Vector2f(tile->position.x, tile->position.y);
    this->texture=tile->texture;
    this->texSize=tile->texture.getSize();
    this->tileID=tile->tileID;
    return *this;
}

Tile::Tile(const std::string& filePath, float x, float y, int tileID){
    // std::cout<<"creating a tile\n\n";
    try {

        if (!texture.loadFromFile(filePath)) {
            throw TextureLoadingException(filePath);
        }
        texSize=texture.getSize();
        position.x = x;
        position.y = y;
        this->tileID=tileID;

    }catch ([[maybe_unused]] TextureLoadingException &texErr) {
        try {
            if (!texture.loadFromFile("Textures/Lbozo.png")) {
                throw TextureLoadingException("Textures/Lbozo.png");
            }
            texSize=texture.getSize();
            position.x = x;
            position.y = y;
            this->tileID=tileID;

        }catch ([[maybe_unused]] TextureLoadingException& severeTexErr) {
            std::cerr<<"error image has an error :/\n";
        }
    }

}

Tile::Tile(const Tile &t)  {
    // std::cout<<"creating a tile\n\n";
    position = t.position;
    texture = t.texture;
    texSize = t.texSize;
    this->tileID=t.tileID;
}

Tile::Tile(const Tile &t, float x, float y, int tileID) {
    // std::cout<<"creating a tile\n\n";
    position=sf::Vector2f(x, y);
    texture=t.texture;
    texSize=texture.getSize();
    this->tileID=tileID;
}

void Tile::drawTile(sf::RenderWindow &window) const {
    //draws tile on screen
    sf::Sprite sprite(texture);
    sprite.setOrigin(sf::Vector2f(texSize.x/2,texSize.y/2));
    sprite.setPosition(sf::Vector2f(position.x,position.y));
    sprite.setScale(sf::Vector2f(1, 1));
    window.draw(sprite);
}
