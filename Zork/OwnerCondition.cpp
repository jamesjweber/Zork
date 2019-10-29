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
        if(tag.compare("object") == 0){
        	object = node->value();
        }
        else if(tag.compare("owner") == 0){
        	owner = node->value();
        }
        else if(tag.compare("has") == 0){
        	if(string(node->value()).compare("yes") == 0){
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
	//cout << "EVAL OWNER CONDITION" << endl;
    //cout << "Owner: " << owner << endl;
    //cout << "Object: " << object << endl;
    bool inRoom = z.roomObjs.find(owner) != z.roomObjs.end();
	bool inContainer = z.containerObjs.find(owner) != z.containerObjs.end();

	if(owner == "inventory"){
        
		bool inInventory = z.inventory.find(object) != z.inventory.end();
		if((inInventory && has) || (!inInventory && !has)){
            //cout << "EVAL INVENTORY TRUE has: " << has << " , object: " << object << endl;
            return true;
		}
		else{
			//cout << "EVAL INVENTORY FALSE has: " << has << " , object: " << object << endl;
            return false;
		}
	}
	else if(inRoom){
		Room * tempRoom = z.roomObjs[owner];
		bool found = tempRoom->itemObj.find(object) != tempRoom->itemObj.end();

		if((found && has) || (!found && !has)){
			//cout << "EVAL ROOM TRUE has: " << has << " , object: " << object << endl;
            return true;
		}
		else{
			//cout << "EVAL ROOM false has: " << has << " , object: " << object << endl;
            return false;
		}
	}
	else if(inContainer){
        
		Container * c = z.containerObjs[owner];
		bool found = c->items.find(object) != c->items.end();
		if((found && has) || (!found && !has)){
			//cout << "EVAL Container true has: " << has << " , object: " << object << endl;
            return true;
		}
		else
		{
			//cout << "EVAL Container false has: " << has << " , object: " << object << endl;
            return false;
		}
	}
	return false;

}
