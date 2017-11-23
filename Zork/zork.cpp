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
    
    //Create and iterator
    map<string,xml_node<> *>::iterator it;
    //Set the iterator to the beginning of the map
    for(it = room.begin(); it != room.end(); it++)
    {
        Room * r = nodeToRoom(it->second);
        roomObj.push_back(r);
    }
    for(it = item.begin(); it != item.end(); it++){
        Item * i = new Item(item[it->first]);
        itemObj.push_back(i);
    }
    for(it = container.begin(); it != container.end(); it++){
        Container * c = new Container();
        containerObj.push_back(c);
    }
    for(it = creature.begin(); it != creature.end(); it++){
        Creature * cr = new Creature();
        creatureObj.push_back(cr);
    }
    
}

void Zork::StartGame(){

    // Sets current room as first room (Entrance)
    std::list<Room *>::iterator itr = roomObj.begin();
    currentRoom = *itr; //cout << currentRoom->name << endl;
    
    loadCurrentRoom(currentRoom);
    
    /* Gets inputs and evaluates them word by word */
    int i = 0;
    while(i++ < 200) {
        getInput();
        list<string>::iterator it;
        string s;
        for(it = inputs.begin(); it != inputs.end(); it++){
            s = *it;
            if(it == inputs.begin()){
                evalInput(s,"");
            } else {
                evalInput(s, *(--it));
                it++; // corrects for --it above, otherwise infinite loop
            }
        }
        
    }
}

Room* Zork::nodeToRoom(xml_node<>* roomNode){

	//Room * r = new Room(it->second, item, container, creature);

	Room * r = new Room(); //Start with a default room object

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
            // cout << "name - " << node->value() << endl;
        }
        else if(tag.compare("description") == 0){
        	r->description = node->value();
            // cout << " description - " << node->value() << endl;
        }
        else if(tag.compare("item") == 0){
        	Item* i = nodeToItem(item[node->value()]);
        	r->itemObj.push_back(i);
            cout << "  item - " << node->value() << endl;
        }
        else if(tag.compare("container") == 0){
        	Container* c = nodeToContainer(container[node->value()]);
        	r->containerObj.push_back(c);
            // cout << "    container - " << node->value() << endl;
        }
        else if(tag.compare("border") == 0){
        	xml_node<> * borderName = node->first_node("name");
        	xml_node<> * borderDir = node->first_node("direction");
        	// cout << "   Border - "<<node->first_node("name")->value() << " : " << node->first_node("direction")->value() << endl;
        	r->borders[borderDir->value()] = borderName->value();
        }
        else if(tag.compare("creature") == 0){
        	Creature* c = nodeToCreature(container[node->value()]);
        	r->creatureObj.push_back(c);
            //cout << "    creature - " << node->value() << endl;
        }
	}
	return r;

}

Item* Zork::nodeToItem(xml_node<>* containerNode){
	Item* i = new Item(containerNode);
	return i;
}
Container* Zork::nodeToContainer(xml_node<>* containerNode){
	Container* c = new Container(containerNode);
	return c;
}
Creature* Zork::nodeToCreature(xml_node<>* creatureNode){
	Creature* cr = new Creature(creatureNode);
	return cr;
}

void Zork::getInput(){
    int i = 0;
    int wordStart = 0; //index to keep track of beginning of words
    string input;
    string word;
    string space = " ";
    cout << ">> ";
    getline(cin, input);
    
    inputs.clear();
    
    // Split up words -----------------------------------
    while(i != input.length()){
        if(input[i] == space[0]){
            word = input.substr(wordStart,i-wordStart);
            wordStart = i + 1;
            inputs.push_back(word);
        }
        i++;
    }
    word = input.substr(wordStart,i-wordStart);
    inputs.push_back(word);
    // ---------------------------------------------------
}

bool Zork::evalInput(string s, string prevS){
    
    bool valid = false;
    if(s == "help"){
        cout << "∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆\n"
        "----------------------------- LIST OF ZORK COMMANDS -----------------------------\n"
        "∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇\n\n"
        "[n,s,e,w] - Movement commands\n"
        "[i] - Shows the player's inventory\n"
        "[take] (item) - Allows a user to take an item from an inventory\n"
        "[open] (container) - Prints the contents of an inventory\n"
        "[read] (item) - Prints whatever is written on an object\n"
        //"[drop] (tim) - Drops Tim Dotson from Beta Theta Pi\n"
        "[drop] (item) - Drop item from inventory into current rooom\n"
        "[put] (item) in (container) - Adds the item to the conatiner's inventory\n"
        "[turn on] (item) - Activates item\n"
        "[attack] (creature) with (item) - Pretty self explanatory, it will do as it says\n"
        ""<< endl;
        valid = true;
    }
    if(s == "n" | s == "north"){
        cout << endl;
        valid = true;
    }
    if(s == "s" | s == "south"){
        cout << endl;
        valid = true;
    }
    if(s == "e" | s == "east"){
        cout << endl;
        valid = true;
    }
    if(s == "w" | s == "west"){
        cout << endl;
        valid = true;
    }
    if(s == "i"){
        printInventory();
        valid = true;
    }
    
    for(list<Item *>::iterator itr = currentRoom->itemObj.begin(); itr != currentRoom->itemObj.end(); itr++){
        for(list<Item *>::iterator it = itemObj.begin(); it != itemObj.end(); it++){
            if(s == (*itr)->name && s == (*it)->name && prevS == "take"){
                inventory.push_back(*it);
            }
        }
    }
    return valid;
}

void Zork::parseAction(string){}

void Zork::loadCurrentRoom(Room * room){
    cout << room->description << endl << endl;
}

void Zork::printInventory(void){
    list<Item *>::iterator it;
    cout << endl << "Inventory:" << endl;
    for(it = inventory.begin(); it != inventory.end(); it++){
        cout << "   " << (*it)->name << endl;
    }
    cout << endl;
}
