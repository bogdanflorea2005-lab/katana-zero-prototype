//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include "Entity.h"
#include "SFML/Graphics.hpp"


class Camera;
class Player;

class Enemy: public Entity {
private:
    void moveLeft() override;
    void moveRight() override;
    void gravity() override;
    void stopMovement() override;

public:
    Enemy()=default;
    Enemy(const std::string &filePath, float x, float y);

    void camMoveLeft(float velo);
    void camMoveRight(float velo);
    void camMoveUp(float velo);
    void camMoveDown(float velo);

    void drawEnemy(sf::RenderWindow &window);

    void seekPlayer(Player& p);

    Enemy &operator=(Enemy* enemy);

};


#endif //OOP_ENEMY_H