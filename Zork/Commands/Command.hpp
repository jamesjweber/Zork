#ifndef Command_hpp
#define Command_hpp

#include <stdio.h>
class Command
{
public:
    Command();
    virtual ~Command();
    
    virtual void get();
};
#endif /* Command_hpp */
