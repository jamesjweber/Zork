/*
 * Zork.h
 *
 *  Created on: Nov 3, 2017
 *      Author: millerev
 */

#ifndef ZORK_H_
#define ZORK_H_

#include "rapidxml.hpp"

class Item;
class Containter;
class Trigger;
class Room;
class Creature;


#include <string>;
#include <map>;
#include <queue>;
#include <vector>;

using namespace std;
using namespace rapidxml;

class Zork {
public:
	Zork();
	virtual ~Zork();


	string userInput;
	map<string, Item*> inventory;
	map<string, Item*> items;
	map<string , Room*> rooms;
	map<string, Creature*> creatures;
	map<string, Trigger*> triggers;

	void setUpGame(string);
	void StartGame();
	void checkTriggers();
	void evalInput(string);
	void parseAction(string);
	void getSibling(xml_node<>* root);


};

#endif /* ZORK_H_ */
