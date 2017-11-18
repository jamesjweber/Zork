/*
 * Zork.h
 *
 *  Created on: Nov 3, 2017
 *      Author: millerev
 */

#ifndef ZORK_H_
#define ZORK_H_

#include "rapidxml.hpp"

/*class Item;
class Containter;
class Trigger;
class Room;
class Creature; */

#include <list>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include "Room.h"

using namespace std;
using namespace rapidxml;

class Zork {
public:
	Zork(string s);
	virtual ~Zork();

	string userInput;
	/* map<string, Item*> inventory;
	map<string, Item*> items;
	map<string , Room*> rooms;
	map<string, Creature*> creatures;
	map<string, Trigger*> triggers; */

	xml_node<> * setUpGame(string s);
    void makeMap(xml_node<> * mapNode);
	void StartGame();
	void checkTriggers();
	bool evalInput(string);
	void parseAction(string);
	void getSibling(xml_node<>*);
    void loadCurrentRoom(Room *);
    void getInput(void);
private:
    xml_node<> * mapNode;
    map<string, xml_node<> *> room;
    map<string, xml_node<> *> item;
    map<string, xml_node<> *> container;
    map<string, xml_node<> *> creature;
    list<Room *> roomObj;
    list<string> inputs;
    Room * currentRoom;
};

#endif /* ZORK_H_ */
