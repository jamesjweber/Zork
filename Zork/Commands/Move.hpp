#ifndef Move_hpp
#define Move_hpp
#include<iostream>

class Move {
public:
    Move(std::string m);
    virtual ~Move();
private:
    std::string dir;
};

#include <stdio.h>

#endif /* Move_hpp */
