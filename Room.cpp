//
// Created by Bogdan on 12/1/2025.
//

#include "Room.h"
#include "Camera.h"
#include "Player.h"

#include "error.h"
#include "PlayerOutOfBoundsException.h"
#include "RoomIDException.h"
#include "TextureLoadingException.h"
#include "SFML/Graphics.hpp"

Room::Room(const std::string& roomID, sf::RenderWindow& window) {
    std::cout<<"creating a room\n\n";
    try {
        /**
     after I figure out how to make a decent file format for loading/saving room data, will use sth. like:
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
     where the file name will also be the room's ID
     **/

        //for now, enemiesKilled will be 0 on launch. After i figure out how to deal with save-states, it will be stored in there
        if (roomID == "test") {
            Player::enemiesKilled=0;
            tileNum=5;
            enemyNum=2;
            roomSize=sf::Vector2f(window.getSize().x, window.getSize().y);
            roomCentre=sf::Vector2f(window.getSize().x/2, window.getSize().y/2);
            checkpointPos=roomCentre;
            std::string tilePath ="Textures/placeholderTile.png";
            std::string tilePath2 ="Textures/placeholderTile2.png";
            std::string enemyPath = "Textures/placeholderEnemy.png";
            tiles[0]=new Tile(tilePath, 300, 500, 1);
            tiles[1]=new Tile(tiles[0], 1100, 450, 2);
            tiles[2]=new Tile(tilePath2, 450, 1050, 3);
            tiles[3]=new Tile(tiles[2], 450+555, 1050, 4);
            tiles[4]=new Tile(tiles[3], 450+555+555, 850, 5);
            {
                /*
                Ok, so, I don't know why, but doing sth like this makes the enemies work, but enemies[i]=new Enemy(data) makes them noclip.
                This means that I will have to fill my enemies[] vector through a locally declared Enemy, instead of re-instantiating them using 'new'.
                That might be caused by a faulty implementation of op= override or cc override, though I don't know why or how that would affect tile collision,
                especially when it works fine for tiles...
                */
                Enemy e1(enemyPath, 1500, 200);
                Enemy e2(enemyPath, 300, 150);
                enemies[0]=e1;
                enemies[1]=e2;
            }

        }else {
            RoomIDException err(roomID);
            tileNum=0;
            enemyNum=0;
            throw err;
        }
    }catch (RoomIDException err) {
        hasError=1;
    }

}

void Room::drawRoom(sf::RenderWindow &window, Player& player, Camera& camera) {
    if (hasError) {
        std::string errFile="Textures/CustomErrorImg.png";
        sf::Texture err;
        try {
            if (!err.loadFromFile(errFile)) {
                TextureLoadingException texErr(errFile);
                throw texErr;
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
        }catch (TextureLoadingException texErr){
            std::cerr<<"error image has an error :/\n";
        }
    }else {
        Entity *p1=&player;
        auto *p=dynamic_cast<Player*>(p1);

        //p->setPosition(sf::Vector2f(-500, -500));
        p->setPosition(roomCentre);
        camera.setOrigin(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

        std::cout<<"tileNum: "<<tileNum<<std::endl<<"enemyNum: "<<enemyNum<<"\n";
        p->coordinates=roomCentre;
        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent())
                if (event->is<sf::Event::Closed>())
                    window.close();

            window.clear();
            /**
                OUT OF BOUNDS ERROR NEEDS TO BE REVISED!!
            **/
            /*try {
                p->coordinates=sf::Vector2f(p->coordinates.x+p->velocity.x, p->coordinates.y+p->velocity.y);
                checkpointPos.x-=p->getVelocity().x;
                checkpointPos.y-=p->getVelocity().y;
                std::cout<<"In room.cpp/drawRoom():\nCoords:\nX: "<<p->coordinates.x<<"\nY: "<<p->coordinates.y<<std::endl;
                if (p->coordinates.x>roomSize.x || p->coordinates.x<(-1)*roomSize.x || p->coordinates.y>roomSize.y || p->coordinates.y<(-1)*roomSize.y) {
                    throw PlayerOutOfBoundsException(*p, p->getPosition());
                }
            }catch (PlayerOutOfBoundsException boundErr) {
                /*
                I will have to either revisit this, or re-write the whole project from scratch, replacing all float variables with integers, and while I'm at it,
                maybe revise tile collision to use a*x+b=y functions, instead of 4 points on a plane for tiles.
                #1#
                p->setPosition(checkpointPos);
                checkpointPos=roomCentre;
                p->velocity=sf::Vector2f(0, 0);
                p->coordinates=roomCentre;
            }*/

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
                Player::tempAttack(enemies[i]);
                enemies[i].drawEnemy(window);
                enemies[i].seekPlayer(*p);
                camera.moveEntityWhenCentering(*p, enemies[i]);
                camera.playerReachedBoundary(*p, enemies[i]);
            }

            camera.centerPlayer(*p);
            window.display();
        }
    }
}
