/*
 * Zork.h
 *
 *  Created on: Nov 3, 2017
 *      Author: millerev
 */

#ifndef ZORK_H_
#define ZORK_H_

#include "rapidxml.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace rapidxml;

class Zork {
public:
	Zork();
	virtual ~Zork();


	string userInput;
	map<string, xml_node<>*> inventory;
	map<string, xml_node<>*> items;
	map<string , xml_node<>*> rooms;
	map<string, xml_node<>*> creatures;
	map<string, xml_node<>*> triggers;

	void setUpGame(string);
	void StartGame();
	void checkTriggers();
	void evalInput(string);
	void parseAction(string);
	void getSibling(xml_node<>* root);


};

#endif /* ZORK_H_ */
