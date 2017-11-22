#include "Move.hpp"
#include <iostream>

Move::Move(std::string m):dir(m)
{
    std::cout << "The direction you entered is " << dir << std::endl;
};
Move::~Move(){};
