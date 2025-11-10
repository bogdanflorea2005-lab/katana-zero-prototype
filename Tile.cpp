//
// Created by Bogdan on 11/7/2025.
//

#include "Tile.h"

Tile::Tile(const std::string filePath, float x, float y){
    texture.loadFromFile(filePath);
    texSize=texture.getSize();
    position.x = x;
    position.y = y;
}

Tile::Tile(const Tile &t)  {
    position = t.position;
    texture = t.texture;
    texSize = t.texSize;
}

Tile::Tile(const Tile &t, float x, float y) {
    position=sf::Vector2f(x, y);
    texture=t.texture;
    texSize=texture.getSize();
}

void Tile::drawTile(sf::RenderWindow &window) {
    sf::Sprite sprite(texture);
    sprite.setOrigin(sf::Vector2f(texSize.x/2,texSize.y/2));
    sprite.setPosition(sf::Vector2f(position.x,position.y));
    sprite.setScale(sf::Vector2f(1, 1));
    window.draw(sprite);
}
