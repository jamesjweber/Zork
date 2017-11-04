//============================================================================
// Name        : zork.cpp
// Author      : Evan Miller
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "rapidxml.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>


using namespace std;
using namespace rapidxml;

void getSibling(xml_node<>* node);

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	xml_document<> doc;
	string filename = "zork.xml";

	ifstream theFile("src/zork.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);

	xml_node<> * root = doc.first_node("map");
	xml_node<> * node = root->first_node();

	getSibling(node);

	return 0;
}

void setUpGame(string){}
void StartGame(){}
void checkTriggers(){}
void evalInput(string){}
void parseAction(string){}
void getSibling(xml_node<>* root){

	xml_node<> * node;
	for(node = root->first_node(); node; node = node ->next_sibling()){
		cout << node->name() << endl;
	}
}
