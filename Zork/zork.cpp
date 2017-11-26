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
#include <string>
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
            room_xml[node->first_node("name")->value()] = node;
        }
        else if (tag.compare("item") == 0){
            //cout << "item" << endl;
            item_xml[node->first_node("name")->value()] = node;
        }
        else if (tag.compare("container") == 0){
            //cout << "container" << endl;
            container_xml[node->first_node("name")->value()] = node;
        }
        else if (tag.compare("creature") == 0) {
            //cout << "creature" << endl;
            creature_xml[node->first_node("name")->value()] = node;
        }
    }
}

void Zork::StartGame(){
    
    //Create and iterator
    map<string,xml_node<> *>::iterator it;
    //Set the iterator to the beginning of the map
    for(it = room_xml.begin(); it != room_xml.end(); it++)
    {
        //Room * r = new Room(it->second, item, container, creature);
        Room* r = nodeToRoom(it->second);
        cout << r->description << endl;
        cout << r->name << endl;
        roomObjs[string(r->name)] = r;
    }
    
    // Sets current room as first room (Entrance)
    currentRoom = roomObjs.begin()->second; //cout << currentRoom->name << endl;
    
    /* Gets inputs and evaluates them word by word */
    int i = 0;
    bool valid = false;
    while(i++ < 200) {
        if(i > 1){
            if(!valid){
                cout << "Your statement could not be interpreted" << endl;
            }
        }
        valid = false;
        getInput();
        list<string>::iterator it;
        string s;
        for(it = inputs.begin(); it != inputs.end(); it++){
            s = *it;
            if(s == "quit" || s == "end"){
                i = 200;
            }
            if(it == inputs.begin()){
                valid += evalInput(s,"");
            } else {
                valid += evalInput(s, *(--it));
                it++; // corrects for --it above, otherwise infinite loop
            }
        }
    }
}

/*void Zork::StartGame(){
    
    // Sets current room as first room (Entrance)
    std::list<string, Room *>::iterator itr = roomObjs.begin();
    currentRoom = *itr; //cout << currentRoom->name << endl;
    
    loadCurrentRoom(currentRoom); */
    
    /* Gets inputs and evaluates them word by word */
    /* int i = 0;
    bool valid = false;
    while(i++ < 200) {
        if(i > 1){
            if(!valid){
                cout << "Your statement could not be interpreted" << endl;
            }
        }
        getInput();
        list<string>::iterator it;
        string s;
        for(it = inputs.begin(); it != inputs.end(); it++){
            s = *it;
            if(s == "quit" || s == "end"){
                i = 200;
            }
            if(it == inputs.begin()){
                valid += evalInput(s,"");
            } else {
                valid += evalInput(s, *(--it));
                it++; // corrects for --it above, otherwise infinite loop
            }
        }
    }
} */

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
        cout << tag << endl;

        if(tag.compare("name") == 0){
        	r->name = node->value();
        	cout << "Room name: " << r->name << endl;
        }
        else if(tag.compare("status") == 0 ){
        	r->status = node->value();
        	cout << "Room status: " << r->status << endl;
        }
        else if(tag.compare("description") == 0){
        	r->description = node->value();
        	cout << "Room description: " << r->description << endl;
        }
        else if(tag.compare("item") == 0){
        	Item* i = nodeToItem(item_xml[node->value()]);
        	cout << "Adding item to room:" << i->name << endl;
        	r->itemObj[i->name] = i;
        	itemObjs.push_back(i);
        	gameObjects[string(i->name)] = i;
        }
        else if(tag.compare("container") == 0){
        	Container* c = nodeToContainer(container_xml[node->value()]);
        	cout << "**Adding container to room..." << c->name << endl;
        	r->containerObj.push_back(c);
        	containerObjs[c->name] = c;
        	gameObjects[string(c->name)] = c;
        }
        else if(tag.compare("border") == 0){

        	cout << "Adding borders to room..." << endl;
        	xml_node<> * borderName = node->first_node("name");
        	xml_node<> * borderDir = node->first_node("direction");
        	cout << "   Border - "<<borderName->value() << " : " << borderDir->value() << endl;
        	string bName = string(borderName->value());
        	string bDir = string(borderDir->value());
        	cout << bName << " : " << bDir << endl;
        	r->borders[bDir] = bName;
        }
        else if(tag.compare("creature") == 0){
        	cout << "Adding creature to room..." << endl;
        	Creature* c = nodeToCreature(creature_xml[node->value()]);

        	r->creatureObj.push_back(c);

        	creatureObjs.push_back(c);
        	//gameObjects[string(c->name)] = c;
        }
	}
	return r;

}

Item* Zork::nodeToItem(xml_node<>* itemNode){
	Item* i = new Item();
	xml_node<>* node;
	cout << itemNode->first_attribute()<< endl;
	for(node = itemNode->first_node(); node; node = node->next_sibling())
	{
		string tag = node->name();
		cout << "~"<< node->name() << node->value() << endl;
		if(tag.compare("name") == 0){
			i->name = node->value();
			cout << "item: "<< i->name << endl;
		}
		else if(tag.compare("description")==0){
			i->description = node->value();
		}
		else if(tag.compare("writing")==0){
			i->writing = node->value();
		}
		else if(tag.compare("status")){
			i->status = node->value();
		}
		else if(tag.compare("turnon")){
			xml_node<>* tNode;
			for(tNode = node->first_node(); tNode; tNode = tNode->next_sibling()){
				string t = tNode->name();
				if(t.compare("action") == 0){
					i->turnOnActions.push_back(tNode->value());
				}
				else if(t.compare("message") == 0){
					i->onMessages.push_back(tNode->value());
				}
			}
		}

	}
	return i;
}

Container* Zork::nodeToContainer(xml_node<>* containerNode){
	Container* c = new Container();
	xml_node<>* node;
	for(node = containerNode->first_node(); node; node = node->next_sibling())
	{
		string tag = node->name();
		if(tag.compare("name") == 0){
			c->name = node->value();
			cout << "Container name: " << c->name << endl;
		}
		else if(tag.compare("status") == 0){
			c->status = node->value();
			cout << "Container status: " << c->status << endl;
		}
		else if(tag.compare("description") == 0){
			c->description = node->value();
			cout << "Container description: " << c->description << endl;
		}
		else if(tag.compare("accept") == 0){
			c->accepts.push_back(node->value());
			cout << "Container accepts... " << endl;
		}
		else if(tag.compare("item") == 0){

			Item* item = nodeToItem(node);
			cout << "Adding Container item: "<< item->name << endl;
			itemObjs.push_back(item);
			gameObjects[string(item->name)] = item;
			c->items[string(item->name)] = item;

		}
		else if(tag.compare("trigger") == 0){
			c->triggers.push_back(new Trigger(node));
		}
	}
	return c;
}

Creature* Zork::nodeToCreature(xml_node<>* creatureNode){
    Creature* c = new Creature();
	xml_node<>* node;
	for(node = creatureNode->first_node(); node; node = node->next_sibling())
	{
        string tag = node->name();
		if(tag.compare("name")){
			c->name = node->value();
		}
		else if(tag.compare("status")){
			c->status = node->value();
		}
		else if(tag.compare("description")){
			c->description = node->value();
		}
		else if(tag.compare("vulnerability")){
			c->vulnerability.push_back(node->value());
		}
		else if(tag.compare("trigger") == 0){
			Trigger* t = new Trigger();
			c->triggers.push_back(t);
		}
	}
	return c;
}
Trigger* Zork::nodeToTrigger(xml_node<>* triggerNode){
	//xml_node<>* node;
	Trigger* trigger = new Trigger();
	return trigger;

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
        cout << endl;
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
    
    for(auto &i : currentRoom->itemObj){
        for(auto &j: itemObjs){
            if(i.second == j && prevS == "take"){
                inventry.push_back(j);
                valid = true;
                goto exit;
            }
        }
    }
    
exit:
    
    if(s == "quit" || s == "end"){
        valid = true;
    }
    
    return valid;
}

void Zork::parseAction(string){}

void Zork::loadCurrentRoom(Room * room){
    cout << room->description << endl << endl;
}

/* James */
void Zork::printInventory(void){
    list<Item *>::iterator it;
    cout << endl << "Inventory:" << endl;
    for(it = inventry.begin(); it != inventry.end(); it++){
        cout << "   " << (*it)->name << endl;
    }
    cout << endl;
}
