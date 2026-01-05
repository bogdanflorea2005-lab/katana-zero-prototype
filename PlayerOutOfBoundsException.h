//
// Created by Bogdan on 12/4/2025.
//

#ifndef OOP_PLATEROUTOFBOUNDSEXCEPTION_H
#define OOP_PLATEROUTOFBOUNDSEXCEPTION_H

#include <iostream>

#include "Player.h"


class PlayerOutOfBoundsException final : public std::exception {
public:
    PlayerOutOfBoundsException() {
        std::cerr << "\nYou managed to get out of bounds. Sorry about that...\n";
    } ;
};


#endif //OOP_PLATEROUTOFBOUNDSEXCEPTION_H