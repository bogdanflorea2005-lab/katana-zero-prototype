//
// Created by Bogdan on 12/3/2025.
//

#ifndef OOP_ROOMIDEXCEPTION_H
#define OOP_ROOMIDEXCEPTION_H
#include <iostream>
#include <stdexcept>

#include "Room.h"


class RoomIDException: public std::exception {
    public:
    RoomIDException(std::string roomID) {
        std::cerr<<"ERROR WHEN LOADING ROOM! Inserted ID is: "<<roomID<<", which is invalid!\n";
    }

};


#endif //OOP_ROOMIDEXCEPTION_H