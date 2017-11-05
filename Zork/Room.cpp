/*
 * Room.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: millerev
 */

#include "Room.h"

Room::Room() {
	// TODO Auto-generated constructor stub

}

Room::Room(xml_node<>* roomNode){
	xml_node<>* node = roomNode->first_node();

	for(node = roomNode->first_node(); node; node = node->next_sibling()){
        string tag = node->name();
        
        if(tag.compare("name") == 0){}
		else if(tag.compare("item") == 0){}
		else if(tag.compare("container") == 0){}
        else if(tag.compare("border") == 0){getBorders(node);}
		else if(tag.compare("creature") == 0){}
	}

}

Room::~Room() {
	// TODO Auto-generated destructor stub
}

bool Room::hasItem(string i){
	for (std::list<string>::iterator it=items.begin(); it!=items.end(); it++){
		cout << "item found: " << i << endl;
		return true;
	}
	cout << "item not found: " << i << endl;
	return false;
}
void Room::evalTriggers(){

}

void Room::getBorders(xml_node<> * borderNode){
    xml_node<> * borderName = borderNode->first_node("name");
    xml_node<> * borderDir = borderNode->first_node("direction");
    borders[borderDir->value()] = borderName->value();
}


>>>>>>> fefe4840c22b5136bb72612ca6977cfedbbceffb
