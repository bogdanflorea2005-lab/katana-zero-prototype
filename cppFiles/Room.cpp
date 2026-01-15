//
// Created by Bogdan on 12/1/2025.
//

#include "../Headers/Room.h"
#include "../Headers/Camera.h"
#include "../Headers/Player.h"

#include "../Headers/ParticleFactory.h"
#include "../Headers/PlayerOutOfBoundsException.h"
#include "../Headers/RoomIDException.h"
#include "../Headers/TempClass.h"
#include "../Headers/TextureLoadingException.h"
#include "SFML/Graphics.hpp"

Room::Room(const std::string& roomID, sf::RenderWindow& window) {
    std::cout<<"creating a room\n\n";
    try {
            //for now, enemiesKilled will be 0 on launch. After I figure out how to deal with save-states, it will be stored in there
        if (roomID == "test") {
            Player::enemiesKilled=0;

            particleNum=1;
            entityNum=7;
            roomSize=sf::Vector2f(window.getSize().x, window.getSize().y);
            roomCentre=sf::Vector2f(window.getSize().x/2, window.getSize().y/2);
            checkpointPos=roomCentre;
            std::string tilePath ="Textures/placeholderTile.png";
            std::string tilePath2 ="Textures/placeholderTile2.png";
            std::string enemyPath = "Textures/placeholderEnemy.png";
            particleKeys[0]="Textures/Particle.png";
            //initialized counters and texture paths.

            tileStartPos=0;
            entities.push_back(std::make_shared<Tile>(tilePath, 300, 500, 1));
            entities.push_back(std::make_shared<Tile>(tilePath, 1100, 450, 2));
            entities.push_back(std::make_shared<Tile>(tilePath2, 450, 1050, 3));
            entities.push_back(std::make_shared<Tile>(tilePath2, 450+555, 1050, 4));
            entities.push_back(std::make_shared<Tile>(tilePath2, 450+555+555, 850, 5));
            tileEndPos=5;
            //initialized tiles
            enemyStartPos=5;
            {
                Enemy e1(enemyPath, 1500, 200);
                Enemy e2(enemyPath, 300, 150);
                entities.push_back(std::make_shared<Enemy>(e1));
                entities.push_back(std::make_shared<Enemy>(e2));
            }
            enemyEndPos=7;
            //initialized enemies

        }else {
            RoomIDException err(roomID);
            throw err;
            //error thrown in case of invalid roomID
        }
    }catch (RoomIDException err) {
        hasError=true;
        //this gets used in drawRoom() to handle the roomID error.
    }

}

void Room::drawRoom(sf::RenderWindow &window, Player& player, Camera& camera) {
    if (hasError) {
        std::string errFile="Textures/Mihaita-Dragan.png";
        try {
            sf::Texture err;
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

        p->setPosition(roomCentre);
        camera.setOrigin(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

        p->coordinates=roomCentre;
        //initializing player data
        ParticleFactory particleFactory;

        for (int i=enemyStartPos; i<enemyEndPos; i++) {
            p->registerEnemy(dynamic_cast<Enemy*>(entities.at(i).get()));
        }
        //registering enemies for player to send data to

        int a=1, b=2;
        TempClass t1(*p, a);
        t1.display();

        TempClass t2(a, b);
        t2.display();
        std::cout<<t2.varFunc(a, b)<<"\n";
        //template class use

        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent())
                if (event->is<sf::Event::Closed>())
                    window.close();

            window.clear();
            /**
                OUT OF BOUNDS ERROR NEEDS TO BE REVISED!!
            **/
            try {
                p->coordinates=sf::Vector2f(p->coordinates.x+p->velocity.x, p->coordinates.y+p->velocity.y);
                checkpointPos.x-=p->getVelocity().x;
                checkpointPos.y-=p->getVelocity().y;
                //std::cout<<"In room.cpp/drawRoom():\nCoords:\nX: "<<p->coordinates.x<<"\nY: "<<p->coordinates.y<<std::endl;
                if (p->coordinates.x>roomSize.x || p->coordinates.x<(-1)*roomSize.x || p->coordinates.y>roomSize.y || p->coordinates.y<(-1)*roomSize.y) {
                    throw PlayerOutOfBoundsException();
                }
            }catch (PlayerOutOfBoundsException boundErr) {
                /*
                Teleportation is inaccurate due to floating point inaccuracy
                */
                p->setPosition(checkpointPos);
                checkpointPos=roomCentre;
                p->velocity=sf::Vector2f(0, 0);
                p->coordinates=checkpointPos;
            }


            for (int j=0; j<50; j++) {
                for (int i=0; i<particleNum; i++) {
                    particleFactory.getParticle(particleKeys[i])->draw(sf::Vector2f(rand()%1900, rand()%1000), window);
                }
                //fills screen with particles
            }

            p->drawPlayer(window);
            p->movement();

            for (int i=tileStartPos; i<tileEndPos; i++) {
                //checking tile collision for player
                auto tile=dynamic_cast<Tile*>(entities.at(i).get());
                p->checkCollision(*tile);
            }

            for (int i=tileStartPos; i<tileEndPos; i++) {
                auto tile=dynamic_cast<Tile*>(entities.at(i).get());
                tile->drawTile(window);
                camera.playerReachedBoundary(*p, *tile);
                camera.moveEntityWhenCentering(*p, *tile);
                //moving tiles when player interacts with camera
                for (int j=enemyStartPos; j<enemyEndPos; j++) {
                    auto enemy=dynamic_cast<Enemy*>(entities.at(j).get());
                    enemy->checkCollision(*tile);
                    //checking tile collision for enemies
                }
            }

            for (int i=enemyStartPos; i<enemyEndPos; i++) {
                auto enemy=dynamic_cast<Enemy*>(entities.at(i).get());
                Player::tempAttack(*enemy);
                enemy->drawEnemy(window);
                camera.moveEntityWhenCentering(*p, *enemy);
                camera.playerReachedBoundary(*p, *enemy);
                //moving enemies when player interacts with camera
            }
            camera.centerPlayer(*p);
            //centers player to middle of screen
            window.display();
        }
        for (int i=enemyStartPos; i<enemyEndPos; i++) {
            auto enemy=dynamic_cast<Enemy*>(entities.at(i).get());
            p->removeEnemy(enemy);
            //removes enemies from enemies vector in Player()
        }
    }
}
