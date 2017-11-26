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
	//string status;  - inherited from GameObject
	string description;
	vector<string> accepts;
	map<string, Item*> items;
    //vector<Trigger> triggers;

    bool hasItem(string item);
    void checkTriggers();
    void checkAccept();
};

#endif /* ZORK_CONTAINER_H_ */
