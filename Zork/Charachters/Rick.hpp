#ifndef Rick_hpp
#define Rick_hpp

#include <stdio.h>

class Rick: public Human{
public:
    Rick();
    virtual ~Rick();
private:
    int health;
    //World location;
};

#endif /* Rick_hpp */
