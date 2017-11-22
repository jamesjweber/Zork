//============================================================================
// Name        : zork.cpp
// Author      : Evan Miller
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Zork.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <list>
#include "rapidxml.hpp"
#include "Room.h"

Zork::Zork(string filename) {
    mapNode = setUpGame(filename);
    makeMap(mapNode);
    StartGame();
}

Zork::~Zork() {
    
}

void Zork::getSibling(xml_node<>* root){
    
    xml_node<> * node;
    for(node = root->first_node(); node; node = node ->next_sibling())
    {
        std::cout << node->name() << endl;
    }
}
xml_node<> * Zork::setUpGame(string s){
    xml_document<> doc;
    
    ifstream theFile(s);
    
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);
    
    xml_node<> * root = doc.first_node();
    
    /*
     
     */
    
    return (root);
}
void Zork::makeMap(xml_node<> * mapNode) {
    xml_node<> * node = mapNode->first_node();
    
    for(;node != NULL ;node = node->next_sibling()) {
        string tag = node->name();
        
        if(tag.compare("room") == 0){
            //cout << "room" << endl;
            room[node->first_node("name")->value()] = node;
        }
        else if (tag.compare("item") == 0){
            //cout << "item" << endl;
            item[node->first_node("name")->value()] = node;
        }
        else if (tag.compare("container") == 0){
            //cout << "container" << endl;
            container[node->first_node("name")->value()] = node;
        }
        else if (tag.compare("creature") == 0) {
            //cout << "creature" << endl;
            creature[node->first_node("name")->value()] = node;
        }
    }
}

void Zork::StartGame(){
    
    //Create and iterator
    map<string,xml_node<> *>::iterator it;
    //Set the iterator to the beginning of the map
    for(it = room.begin(); it != room.end(); it++)
    {
        //Room * r = new Room(it->second, item, container, creature);
    	Room * r = nodeToRoom(it->second);

        roomObj.push_back(r);
    }
    
    list<Room *>::iterator itr;
    
    for(itr = roomObj.begin(); itr != roomObj.end(); itr++){
        
    }
    
    
    
    //Create and iterator
    /* map<string,xml_node<> *>::iterator it;
     //Set the iterator to the beginning of the map
     for(it = room.begin(); it != room.end(); it++)
     {
     cout << it->first << " : " << it->second->name() << endl;
     }
     for(it = item.begin(); it != item.end(); it++)
     {
     cout << it->first << " : " << it->second->name() << endl;
     }
     for(it = container.begin(); it != container.end(); it++)
     {
     cout << it->first << " : " << it->second->name() << endl;
     }
     for(it = creature.begin(); it != creature.end(); it++)
     {
     cout << it->first << " : " << it->second->name() << endl;
     } */
}

Room* Zork::nodeToRoom(xml_node<>* roomNode){

	//Room * r = new Room(it->second, item, container, creature);

	Room *r = new Room(); //Start with a default room object

	//xml_node<>* node = roomNode->first_node();


	xml_node<>* node; //roomNode is already passed in


	//NOTE: Common approach
	//	1. set the room field to a string (i.e. name, description)
	//	2. Look up the right object node, make that object, add it to the
	//	   list of objects in the room:
	//	   example:
	//     SomeObject* o = nodeToSomeObject(map[node->value()]);
	//	   objectList.push_back(o);

	//     		- map[node->value()] returns an xml_node<>*
	//			-nodeToSomeObject takes a node, makes a new object
	//			-Lastly, push the object onto the room list
	// 3.  Go through the xml_node (i.e. borders)


	for(node = roomNode->first_node(); node; node = node->next_sibling())
	{
        string tag = node->name();

        if(tag.compare("name") == 0){
        	r->name = node->value();

        }
        else if(tag.compare("description") == 0){
        	r->description = node->value();
        }
        else if(tag.compare("item") == 0){
        	Item* i = nodeToItem(item[node->value()]);
        	r->itemObj.push_back(i);
        }
        else if(tag.compare("container") == 0){
        	Container* c = nodeToContainer(container[node->value()]);
        	r->containerObj.push_back(c);
        }
        else if(tag.compare("border") == 0){
        	xml_node<> * borderName = node->first_node("name");
        	xml_node<> * borderDir = node->first_node("direction");
        	cout << "   Border - "<<node->first_node("name")->value() << " : " << node->first_node("direction")->value() << endl;
        	r->borders[borderDir->value()] = borderName->value();
        }
        else if(tag.compare("creature") == 0){
        	Creature* c = nodeToCreature(container[node->value()]);
        	r->creatureObj.push_back(c);
        }
	}
	return r;

}

Item* Zork::nodeToItem(xml_node<>* containerNode){
	Item* i = new Item();
	return i;
}
Container* Zork::nodeToContainer(xml_node<>* containerNode){
	Container* c = new Container();
	return c;
}
Creature* Zork::nodeToCreature(xml_node<>* containerNode){
	Creature* c = new Creature();
	return c;
}

void checkTriggers(){}
void evalInput(string){}
void parseAction(string){}
