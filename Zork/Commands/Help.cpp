#include "Help.hpp"
#include <iostream>

Help::Help(){
    std::cout << "See list of commands \n\n"
"   Movements:\n"
"       n: move north\n"
"       s: move south\n"
"       e: move east \n"
"       w: move west \n\n"
"   "<< std::endl;
}

Help::~Help(){}
