#ifndef Input_hpp
#define Input_hpp
#include <iostream>

#include <stdio.h>
class Input{
public:
    Input();
    virtual ~Input();
    
    virtual bool verify(const std::string &check, const std::string &given);
};
#endif /* Input_hpp */
