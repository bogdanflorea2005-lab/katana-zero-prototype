//
// Created by Bogdan on 03-Jan-26.
//

#ifndef OOP_TEMPCLASS_H
#define OOP_TEMPCLASS_H
#include <iostream>


template <typename T1, typename T2> class TempClass {
/*
this is a template class that I don't know what to do with. I cannot find a use for templates for specifically this project,
though I am aware of its uses in making databases. I simply do not know how to implement a template class in my code without
overcomplicating things or straight up breaking them, especially since I don't need any of its benefits, since I need to use
specific data types for everything and don't need to make something that functions with any data type
*/
private:
    T1 disp1;
    T2 disp2;
public:
    TempClass(T1 &x, T2 &y): disp1(x), disp2(y) {}

    void display() {
        std::cout<<"disp1:\n"<<disp1<<"\ndisp2:\n"<<disp2<<"\n\n";
        std::cout<<"This would be so useful in a database!\n";
    }

static T1 varFunc(T1 x, T1 y) {
        return x+y;
    }


};


#endif //OOP_TEMPCLASS_H