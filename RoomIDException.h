//
// Created by Bogdan on 12/3/2025.
//

#ifndef OOP_ROOMIDEXCEPTION_H
#define OOP_ROOMIDEXCEPTION_H
#include <iostream>

#include "Room.h"


class RoomIDException final : public std::exception {
    public:
    explicit RoomIDException(const std::string &roomID) {
        std::cerr<<"ERROR WHEN LOADING ROOM! Inserted ID is: "<<roomID<<", which is invalid!\n";
    }

};


#endif //OOP_ROOMIDEXCEPTION_H