/*
 * Creature.h
 *
 *  Created on: Nov 5, 2017
 *      Author: millerev
 */ 

#ifndef ZORK_CREATURE_H_
#define ZORK_CREATURE_H_

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;
class Creature {
public:
	Creature();
	Creature(xml_node<>* creatureNode);
	virtual ~Creature();
	string name;
	string status;
	string description;
	list<string> vulnerability;
	//attack
	//trigger
	void attack();
	void checkTriggers();

};

#endif /* ZORK_CREATURE_H_ */
