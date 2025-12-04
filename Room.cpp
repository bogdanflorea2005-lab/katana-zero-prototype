//
// Created by Bogdan on 12/1/2025.
//

#include "Room.h"
#include "Camera.h"
#include "Player.h"

#include "error.h"
#include "roomIDError.h"
#include "SFML/Graphics.hpp"

Room::Room(std::string roomID) {
    try {
        /**
     after I figure out how to make a decent file format for loading/saving room data, will use sth. like:\n
     if(roomID == "id"){
        tileNum=sthFromFile;
        enemyNum=sthElseFromFile;
        for(int i=0; i<tileNum; i++){
            //read tile data for all tiles from file
        }
        for(int i=0; i<enemyNum; i++){
            //read enemy data for all enemies from file
        }
     }
     **/
        if (roomID == "test") {
            tileNum=5;
            enemyNum=2;
            checkpointPos=sf::Vector2f(1000, 400);
            std::string tilePath ="Textures/placeholderTile.png";
            std::string tilePath2 ="Textures/placeholderTile2.png";
            std::string enemyPath = "Textures/placeholderEnemy.png";
            tiles[0]=new Tile(tilePath, 300, 500, 1);
            tiles[1]=new Tile(tiles[0], 1100, 450, 2);
            tiles[2]=new Tile(tilePath2, 450, 850, 3);
            tiles[3]=new Tile(tiles[2], 450+555, 850, 4);
            tiles[4]=new Tile(tiles[3], 450+555+555, 650, 5);
            enemies[0]=new Enemy(enemyPath, 1500, 200);
            enemies[1]=new Enemy(enemyPath, 300, 150);
        }else {
            roomIDError err;
            throw err;
        }
    }catch (roomIDError err) {
        std::cerr<<"ERROR LOADING ROOM";
        hasError=1;
    }

}

void Room::drawRoom(sf::RenderWindow &window, Player& player, Camera& camera) {
    if (hasError) {
        std::string errFile="Textures/PROSTJEGOSFMM.png";
        sf::Texture err;
        if (!err.loadFromFile(errFile)) {
            std::cerr<<"ERROR LOADING PROSTJEGOS\n";
            err.loadFromFile("Textures/Lbozo.png");
        }
        sf::Sprite errSprite(err);
        errSprite.setTexture(err);
        errSprite.setScale(sf::Vector2f(1, 1));
        errSprite.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
        int timer=0;
        while (timer<288) {
            window.clear();
            window.draw(errSprite);
            timer++;
            window.display();
        }
        window.close();
    }

    Entity *p1=&player;
    auto *p=dynamic_cast<Player*>(p1);

    p->setPosition(checkpointPos);
    camera.setOrigin(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

    std::cout<<"tileNum: "<<tileNum<<std::endl<<"enemyNum: "<<enemyNum<<"\n";
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

        window.clear();

        camera.drawCambox(window, "Textures/CameraSize.png");
        p->drawPlayer(window);
        p->movement();

        for (int i=0; i<tileNum; i++) {
            p->checkCollision(tiles[i]);
        }

        for (int i=0; i<tileNum; i++) {
            tiles[i].drawTile(window);
            camera.playerReachedBoundary(*p, tiles[i]);
            camera.moveEntityWhenCentering(*p, tiles[i]);
            for (int j=0; j<enemyNum; j++) {
                enemies[j].checkCollision(tiles[i]);
            }
        }

        for (int i=0; i<enemyNum; i++) {
            enemies[i].drawEnemy(window);
            enemies[i].seekPlayer(*p);
            camera.moveEntityWhenCentering(*p, enemies[i]);
            camera.playerReachedBoundary(*p, enemies[i]);
        }

        camera.centerPlayer(*p);
        window.display();
    }
}