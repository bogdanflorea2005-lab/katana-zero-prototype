//
// Created by Bogdan on 12/1/2025.
//

#include "Room.h"

#include "Camera.h"
#include "Player.h"

Room::Room(std::string roomID) {
    try {
        /**
     after I figure out how to make a decent file format for loading/saving room data, will use sth. like:\n
     if(roomID == "id"){
        tileNum=ceva;
        enemyNum=altceva;
        std::fin>>tileNum>>enemyNum;
        for(int i=0; i<tileNum; i++){
            //read tile data for all tiles
        }
        for(int i=0; i<enemyNum; i++){
            //read enemy data for all enemies
        }
     }
     **/
        if (roomID == "test") {
            tileNum=5;
            enemyNum=1;
            checkpointPos=sf::Vector2f(1000, 400);
            std::string tilePath ="Textures/placeholderTile.png";
            std::string tilePath2 ="Textures/placeholderTile2.png";
            std::string enemyPath = "Textures/placeholderEnemy.png";
            int tileNum=5, enemyNum=1;
            tiles[0]=new Tile(tilePath, 300, 500, 1);
            tiles[1]=new Tile(tiles[0], 1100, 450, 2);
            tiles[2]=new Tile(tilePath2, 450, 850, 3);
            tiles[3]=new Tile(tiles[2], 450+555, 850, 4);
            tiles[4]=new Tile(tiles[3], 450+555+555, 650, 5);
            enemies[0]=new Enemy(enemyPath, 1500, 200);
        }else {
            throw 0;
        }
    }catch (int i) {
        std::cerr<<"ROOM ID NOT RECOGNISED!!\n\n";
    }

}

void Room::drawRoom(sf::RenderWindow &window, Player& player, Camera& camera) {
    player.setPosition(checkpointPos);
    camera.setOrigin(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

    std::cout<<"tileNum: "<<tileNum<<std::endl<<"enemyNum: "<<enemyNum<<"\n";
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();
        window.clear();

        camera.drawCambox(window, "Textures/CameraSize.png");
        player.drawPlayer(window);
        player.movement();

        for (int i=0; i<tileNum; i++) {
            player.checkCollision(tiles[i]);
        }

        for (int i=0; i<tileNum; i++) {
            tiles[i].drawTile(window);
            camera.playerReachedBoundary(player, tiles[i]);
            camera.moveEntityWhenCentering(player, tiles[i]);
            for (int j=0; j<enemyNum; j++) {
                enemies[j].checkCollision(tiles[i]);
            }
        }

        for (int i=0; i<enemyNum; i++) {
            enemies[i].drawEnemy(window);
            enemies[i].seekPlayer(player);
            camera.moveEntityWhenCentering(player, enemies[i]);
            camera.playerReachedBoundary(player, enemies[i]);
        }

        camera.centerPlayer(player);

        window.display();

    }
}
