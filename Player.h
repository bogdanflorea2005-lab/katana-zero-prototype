//
// Created by Bogdan on 11/7/2025.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <iostream>

#include "Entity.h"
#include "Camera.h"
#include "Enemy.h"
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <algorithm>


class Player: public Entity {
public:
    static int enemiesKilled;
    //static bool isPlayerDead;

private:
    int spaceTimer=0;
    std::string currentRoom;
    sf::Vector2f coordinates;
    std::vector<Enemy*> enemies; //<-- Observers for Observer pattern

    void moveLeft() override;
    void moveRight() override;
    void gravity() override;
    void stopMovement() override;
    void jump() override;

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();

    void setCurrentRoom(const std::string& roomID);
    std::string getCurrentRoom();

public:
    Player(const std::string &filePath, float x, float y);
    ~Player() {
        std::cout<<"enemies killed: "<<enemiesKilled<<std::endl;
        std::cout<<"deleted player\n";
    };

    /*bool getDead() {
        return isPlayerDead;
    }*/

    void drawPlayer(sf::RenderWindow& window);

    void movement();

    Player &operator=(Player * player);

    static void tempAttack(Enemy& e);

    void registerEnemy(Enemy *enemy);   //
    void removeEnemy(Enemy *enemy);     //  <-- Observer pattern
    void notifyEnemies();               //

    template<typename T3>
    static T3 doSth(T3 &x) {
        ++x;
        return x;
    }

    friend void drawRoom(sf::RenderWindow& window, Player& p, Camera& c, Tile tiles[], int& tileNum, Enemy enemies[], int& enemyNum);

    friend std::ostream& operator<<(std::ostream& os, const Player& p) {
        std::cout<<p.coordinates.x<<" "<<p.coordinates.y<<"\n";
        return os;

    }

    friend class Enemy;
    friend class Camera;
    friend class Room;
};


#endif //OOP_PLAYER_H