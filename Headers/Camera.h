//
// Created by Bogdan on 11/17/2025.
//

#ifndef OOP_CAMERA_H
#define OOP_CAMERA_H
#include "SFML/Graphics.hpp"


class Entity;
class Enemy;
class Tile;

namespace sf {
    class RenderWindow;
}

class Player;

class Camera {
private:
    sf::Vector2f origin;
    const sf::Vector2u size=sf::Vector2u(300, 600);

    void setOrigin(const sf::Vector2f& v);


    bool isTouchingUpper(const Player& p) const;
    bool isTouchingLower(const Player& p) const;
    bool isTouchingLeft(const Player& p) const;
    bool isTouchingRight(const Player& p) const;
    //check if player has touched the boundary set by the camera
    [[nodiscard]] bool isXCentered(const Player& p) const;
    [[nodiscard]] bool isYCentered(const Player& p) const;

public:
    explicit Camera(sf::Vector2f origin);

    //void drawCambox(sf::RenderWindow& window, std::string texFile);

    void playerReachedBoundary(Player& p, Entity& e) const;
    //makes sure the camera follows the player on screen
    void moveEntityWhenCentering(const Player& p, Entity& e) const;
    //moves entities when player touches the camera boundary

    void centerPlayer(Player &p) const;
    //centers player back to center of screen when they stop moving

    friend void drawRoom(sf::RenderWindow& window, Player& p, Camera& c, Tile tiles[], int& tileNum, Enemy enemies[], int& enemyNum);

    friend class Room;
};




#endif //OOP_CAMERA_H
