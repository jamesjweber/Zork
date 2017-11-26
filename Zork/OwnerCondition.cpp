/*
 * OwnerCondition.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: millerev
 */

#include "OwnerCondition.h"
#include "Zork.h"

OwnerCondition::OwnerCondition() {
	// TODO Auto-generated constructor stub

}
OwnerCondition::OwnerCondition(xml_node<>* ownerNode) {
	// TODO Auto-generated constructor stub
	xml_node<>* node;
	owner = "None";
	for(node = ownerNode->first_node(); node; node = node->next_sibling()){
        string tag = node->name();
        if(tag.compare("object")){
        	object = node->value();
        }
        else if(tag.compare("status")){
        	owner = node->value();
        }
        else if(tag.compare("has")){
        	if(strcmp(node->value(),"yes")){
        		has = true;
        	}
        	else{
        		has = false;
        	}
        }

	}
}

OwnerCondition::~OwnerCondition() {
	// TODO Auto-generated destructor stub
}
bool OwnerCondition::eval(Zork& z){
	bool inRoom = z.roomObjs.find(owner) != z.roomObjs.end();
	bool inContainer = z.containerObjs.find(owner) != z.containerObjs.end();

	if(owner == "Inventory"){
		bool inInventory = z.inventory.find(object) != z.inventory.end();
		if((inInventory && has) || (!inInventory && !has)){
			return true;
		}
		else{
			return false;
		}
	}
	else if(inRoom){
		Room * tempRoom = z.roomObjs[owner];
		bool found = tempRoom->itemObj.find(object) != tempRoom->itemObj.end();

		if((found && has) || (!found && !has)){
			return true;
		}
		else{
			return false;
		}
	}
	else if(inContainer){
		Container * c = z.containerObjs[owner];
		bool found = c->items.find(object) != c->items.end();
		if((found && has) || (!found && !has)){
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;

}
