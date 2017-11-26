/*
 * Item.h
 *
 *  Created on: Oct 29, 2017
 *      Author: millerev
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "rapidxml.hpp"

#include <string>
#include <vector>
#include <iostream>
#include "GameObject.h"

#include <stdio.h>

using namespace std;
using namespace rapidxml;

class Item : public GameObject{
public:
	Item();
	Item(xml_node<>* node);
	virtual ~Item();

	string name; //Item name
	string description; //Item description
	string writing; //writing
	//string status;

	vector<string> onMessages; //Messages when the item is used
	vector<string> turnOnActions; //Actions available for the item

	void setUp(xml_node<> *);
	void turnOn(xml_node<> *);

};

#endif /* ITEM_H_ */
