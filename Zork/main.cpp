#include <iostream>
#include "rapidxml.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;
using namespace rapidxml;

int main(int argc, const char * argv[])
{
	cout << "fuck" << endl; // prints !!!Hello World!!!
	xml_document<> doc;
	//string filename = "zork.xml";

	ifstream theFile("Zork/sample.txt.xml");
	cout << "me 2" << endl;

	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);

	xml_node<> * root = doc.first_node();
	//xml_node<> * node = root->first_node();
	cout << root->name()<< endl;
	//getSibling(node);

	return 0;
    return 0;
}
