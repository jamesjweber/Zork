//============================================================================
// Name        : zork.cpp
// Author      : Evan Miller
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "zork.h"

using namespace std;
using namespace rapidxml;

Zork::Zork(){

}
void Zork::getSibling(xml_node<>* node);
void Zork::setUpGame(string){}
void Zork::StartGame(){}
void Zork::checkTriggers(){}
void Zork::evalInput(string){}
void Zork::parseAction(string){}
void Zork::getSibling(xml_node<>* root){

	xml_node<> * node;
	for(node = root->first_node(); node; node = node ->next_sibling())
	{
		std::cout << node->name() << endl;
	}
}
