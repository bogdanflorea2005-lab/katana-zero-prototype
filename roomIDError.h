//
// Created by Bogdan on 12/3/2025.
//

#ifndef OOP_ROOMIDERROR_H
#define OOP_ROOMIDERROR_H
#include <iostream>
#include <stdexcept>


class roomIDError: public std::runtime_error {
    public:
    roomIDError() : std::runtime_error("roomIDError") {
        std::cerr<<"ERROR WHEN LOADING A ROOM\n";
    }
};


#endif //OOP_ROOMIDERROR_H