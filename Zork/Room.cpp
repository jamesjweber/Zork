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
		/*if(node->name() == "name"){}
		else if(node->name() == "item"){}
		else if(node->name() == "container"){

		}
		else if(node->name() == "border"){}
		else if(node->name() == "creature"){}
	*/}

}

Room::~Room() {
	// TODO Auto-generated destructor stub
}
bool Room::hasItem(string i){
	for (std::list<string>::iterator it=items.begin(); it!=items.end(); ++it){
		cout << "item found: " << i << endl;
		return true;
	}
	cout << "item not found: " << i << endl;
	return false;


}
void Room::evalTriggers(){

}


