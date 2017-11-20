/*
 * Room.h
 *
 *  Created on: Nov 3, 2017
 *      Author: millerev
 */

#ifndef ROOM_H_
#define ROOM_H_
#include "rapidxml.hpp"
#include "Borders.h"
#include "Item.h"
#include "Container.h"
#include "Creature.h"
#include <iostream>
#include <list>
#include <string>


//Forward Declarations
//class Item;
//class Container;
//class Trigger;
//class Creature;
//class Borders;

using namespace std;
using namespace rapidxml;

class Room {
public:
	Room();
	Room(xml_node<>* roomNode, map<string, xml_node<> *>,map<string, xml_node<> *>,map<string, xml_node<> *>);
	virtual ~Room();

	string name;
    string description;
	list<Item *> itemObj;
	list<Container *> containerObj;
	map<string,string> borders;
	list<Creature *> creatureObj;
    //list<Trigger> triggers;

	bool hasItem(string i);
	void evalTriggers();
    void getName(xml_node<> *);
    void getDescription(xml_node<> *);
    void getItems(xml_node<> *);
    void getContainers(xml_node<> *);
    void getBorders(xml_node<> *);
    void getCreatures(xml_node<> *);
    void printItems(void);
};

#endif /* ROOM_H_ */
