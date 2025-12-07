//
// Created by Bogdan on 12/4/2025.
//

#ifndef OOP_TEXTURELOADINGEXCEPTION_H
#define OOP_TEXTURELOADINGEXCEPTION_H
#include <iostream>
#include <ostream>
#include <string>
#include <stdexcept>


class TextureLoadingException: public std::exception {
public:
    TextureLoadingException(std::string filePath) {
        std::cerr<<"ERROR LOADING TEXTURE FROM FILE: "<<filePath<<std::endl;
    } ;
};


#endif //OOP_TEXTURELOADINGEXCEPTION_H