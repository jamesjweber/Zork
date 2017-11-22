#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include "rapidxml.hpp"
#include "Room.h"
#include "Item.h"
#include "Zork.h"

using namespace std;
using namespace rapidxml;

int main(int argc, const char * argv[])
{
    Zork * game = new Zork("/Users/jamesweber/Documents/Zork/Zork/Zork/sample.txt.xml");

    // James  -  /Users/jamesweber/Desktop/Xcode/Zork/Zork/sample.txt.xml
    //           /Users/jamesweber/Documents/Zork/Zork/Zork/sample.txt.xml
    // Evan   -  /Zork/sample.txt.xml
    
	return 0;
}
