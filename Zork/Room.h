/*
 * Room.h
 *
 *  Created on: Nov 3, 2017
 *      Author: millerev
 */

#ifndef ROOM_H_
#define ROOM_H_
#include "rapidxml.hpp"
#include <iostream>
#include <list>
#include <string>


//Forward Declarations
//class Item;
//class Container;
//class Trigger;
//class Creature;
//class Borders;
#include "Borders.h"

using namespace std;
using namespace rapidxml;

class Room {
public:
	Room();
	Room(xml_node<>* roomNode);
	virtual ~Room();

	string name;
	list<string> items;
	//list<Container> containers;
	//list<Trigger> triggers;
	map<string, string> borders;
	//list<Creature> creatures;

	bool hasItem(string i);
	void evalTriggers();
	void getBorders(xml_node<>* borderNode);
};

#endif /* ROOM_H_ */
