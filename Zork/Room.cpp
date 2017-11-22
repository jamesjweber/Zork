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

Room::Room(xml_node<>* roomNode, map<string, xml_node<> *> item, map<string, xml_node<> *> container, map<string, xml_node<> *> creature){
	xml_node<>* node = roomNode->first_node();

	for(node = roomNode->first_node(); node; node = node->next_sibling()){
        string tag = node->name();
        
        if(tag.compare("name") == 0){getName(node);}
        else if(tag.compare("description") == 0){getDescription(node);}
        else if(tag.compare("item") == 0){getItems(node);}
        else if(tag.compare("container") == 0){getContainers(node);}
        else if(tag.compare("border") == 0){getBorders(node);}
        else if(tag.compare("creature") == 0){getCreatures(node);}
	}

}

Room::~Room() {
	// TODO Auto-generated destructor stub
}

bool Room::hasItem(string i){
	/* for (std::list<string>::iterator it=items.begin(); it!=items.end(); it++){
		cout << "item found: " << i << endl;
		return true;
	}
	cout << "item not found: " << i << endl;
     */
	return false;
}
void Room::evalTriggers(){

}

void Room::getName(xml_node<> * nameNode){
    name = nameNode->value();
    cout << "Room - " << name << endl;
}
 
void Room::getDescription(xml_node<> * descriptionNode){
    description = descriptionNode->value();
    cout << " Description - " << description << endl;
}

void Room::getItems(xml_node<> * itemNode){
    cout << " Item - " <<itemNode->value() << endl;
    Item * i = new Item();
    itemObj.push_back(i);
}

void Room::getContainers(xml_node<> * containerNode){
    cout << " Container - " << containerNode->value() << endl;
    Container * c = new Container();
    containerObj.push_back(c);
}

void Room::getBorders(xml_node<> * borderNode){
    xml_node<> * borderName = borderNode->first_node("name");
    xml_node<> * borderDir = borderNode->first_node("direction");
    cout << "   Border - "<<borderNode->first_node("name")->value() << " : " << borderNode->first_node("direction")->value() << endl;
    borders[borderDir->value()] = borderName->value();
}

void Room::getCreatures(xml_node<> * creatureNode){
    cout << " Creature - " << creatureNode->value() << endl;
    Creature * c = new Creature();
    creatureObj.push_back(c);
}
