#include "Headers.h"
Command::Command(){};
Command::~Command(){};

void Command::get()
{
    // Declarations
    std::string input;
    Input i;
    
    // Executables
    std::cout << ">> ";
    std::cin >> input;
    
    if (i.verify("help",input))
    {
        Help h;
    }
    if (i.verify("n", input))
    {
        Move m(input);
        ByersHouse b;
        b.getDescription();
    }
}
