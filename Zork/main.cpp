#include <iostream>
#include "Move.hpp"
#include "Command.hpp"

int main(int argc, const char * argv[])
{
    // Declarations
    int n = 3;
    Command c;
    
    // Executables
    while(true)
    {
        c.get();
        n--;
    }
    return 0;
}
