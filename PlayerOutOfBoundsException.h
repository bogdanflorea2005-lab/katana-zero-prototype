//
// Created by Bogdan on 12/4/2025.
//

#ifndef OOP_PLATEROUTOFBOUNDSEXCEPTION_H
#define OOP_PLATEROUTOFBOUNDSEXCEPTION_H

#include <iostream>
#include <stdexcept>

#include "Player.h"


class PlayerOutOfBoundsException: public std::exception {
public:
    PlayerOutOfBoundsException(Player& p, sf::Vector2f position) {
        std::cerr << "\nYou managed to get out of bounds. Sorry about that...\n";
    } ;
};


#endif //OOP_OUTOFBOUNDSEXCEPTION_H