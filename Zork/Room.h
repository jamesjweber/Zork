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
#include "GameObject.h"

class Zork;

using namespace std;
using namespace rapidxml;

class Room : public GameObject{
public:
	Room();
	Room(xml_node<>*, Zork& z);
	Room(xml_node<>* roomNode, map<string, xml_node<> *>,map<string, xml_node<> *>,map<string, xml_node<> *>);
	virtual ~Room();

	string name = "default";
    string description = "default";
	map<string, Item *> itemObj;
	list<Container *> containerObj;
	list<Creature *> creatureObj;
	map<string,string> borders;
	//list<Trigger> triggers;

    void printDescription();
	bool hasItem(string i);
	void evalTriggers();
    void getName(xml_node<> *);
    void getDescription(xml_node<> *);
    void getItems(xml_node<> *);
    void getContainers(xml_node<> *);
    void getBorders(xml_node<> *);
    void getCreatures(xml_node<> *);

};

#endif /* ROOM_H_ */
