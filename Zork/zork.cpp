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
