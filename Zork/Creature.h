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
#include "GameObject.h"

using namespace std;
using namespace rapidxml;
class Creature : public GameObject {
public:
	Creature();
	Creature(xml_node<>* creatureNode);
	virtual ~Creature();
	string name;
	//string status; - in game object
	string description;
	list<string> vulnerability;

	void attack();
	void checkTriggers();

};

#endif /* ZORK_CREATURE_H_ */
