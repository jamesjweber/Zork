/*
 * Container.h
 *
 *  Created on: Nov 4, 2017
 *      Author: millerev
 */

#ifndef ZORK_CONTAINER_H_
#define ZORK_CONTAINER_H_

#include <string>
#include <vector>
#include "Item.h"
#include "rapidxml.hpp"
#include "GameObject.h"

//class Trigger;

using namespace std;
using namespace rapidxml;

class Container : public GameObject {
public:
	Container();
	Container(xml_node<>* containerNode);
	virtual ~Container();

	string name;
	vector<string> accepts;
	map<string, Item*> items;

    bool hasItem(string item);
    void checkTriggers();
    void checkAccept();
    void printContainer();
};

#endif /* ZORK_CONTAINER_H_ */
