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
        gameObjects[r->name] = r;
        cout << r->description << endl;
        cout << r->name << endl;
        roomObjs[string(r->name)] = r;
    }
    
    // Sets current room as first room (Entrance)
    currentRoom = roomObjs.begin()->second; //cout << currentRoom->name << endl;
    currentRoom->printDescription();
    
    /* Gets inputs and evaluates them word by word */
    int i = 0;
    bool valid = false;
    while(i++ < 200) {
        if(i > 1){
            if(!valid){
                cout << endl << "Your statement could not be interpreted" << endl;
            }
        }
        valid = false;
        getInput();
        vector<string>::iterator it;
        for(it = inputs.begin(); it != inputs.end(); it++){
            if(!checkTriggers(true)){
                if(*it == "quit" || *it == "end"){
                    i = 200;
                }
                if(it == inputs.begin()){
                    valid += evalInput(*it,"");
                } else {
                    valid += evalInput(*it, *(--it));
                    it++; // corrects for --it above, otherwise infinite loop
                }
            }
            else{valid = true;}
        }
        checkTriggers(false);
    }
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
        	Container * c = nodeToContainer(container_xml[node->value()]);
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
        else if(tag.compare("trigger") == 0){
            cout << "Adding trigger to room..." << endl;
            Trigger * t = new Trigger(node);
            
            r->triggers.push_back(t);
        }
	}
	return r;
}

Item* Zork::nodeToItem(xml_node<>* itemNode){
	Item* i = new Item();
	xml_node<>* node;
	// cout << itemNode->first_attribute()<< endl;
	for(node = itemNode->first_node(); node; node = node->next_sibling())
	{
		string tag = node->name();
        cout << "~"<< node->name() << ":" <<node->value() << endl;
		if(tag.compare("name") == 0 || tag.compare("") == 0){
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
        else if(tag.compare("trigger") == 0){
            Trigger * t = new Trigger(node);
            i->triggers.push_back(t);
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
		else if(tag.compare("accept") == 0){
			c->accepts.push_back(node->value());
			cout << "Container accepts... " << endl;
		}
		else if(tag.compare("item") == 0){

			Item * item = nodeToItem(node);
			cout << "Adding Container item: "<< item->name << endl;
			itemObjs.push_back(item);
			gameObjects[string(item->name)] = (GameObject *) item;
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
			c->vulnerability.insert(node->value());
		}
		else if(tag.compare("trigger") == 0){
			Trigger* t = new Trigger(node);
			c->triggers.push_back(t);
		}
	}
	return c;
}
Trigger* Zork::nodeToTrigger(xml_node<>* triggerNode){
	//xml_node<>* node;
	Trigger* trigger = new Trigger(triggerNode);
	return trigger;

}

void Zork::getInput(){
    string input;
    cout << endl << ">> ";
    getline(cin, input);
    
    userInput = input;
    
    inputs.clear();
    
    inputs = split(input);
}

vector<string> Zork::split(string input){
    int i = 0;
    int wordStart = 0; //index to keep track of beginning of words
    string word;
    string space = " ";
    vector<string> inputString;
    
    // Split up words -----------------------------------
    while(i != input.length()){
        if(input[i] == space[0]){
            word = input.substr(wordStart,i-wordStart);
            wordStart = i + 1;
            inputString.push_back(word);
        }
        i++;
    }
    word = input.substr(wordStart,i-wordStart);
    inputString.push_back(word);
    // ---------------------------------------------------
    return(inputString);
}

bool Zork::checkTriggers(bool first_check){
    vector<Trigger *>::iterator it;
    vector<string>::iterator actionIterator;
    vector<string>::iterator printIterator;
    map<string, Item *>::iterator itemIterator;
    list<Container *>:: iterator containerIterator;
    list<Creature *>:: iterator creatureIterator;
    bool actionDone = false;
    
    for(it = currentRoom->triggers.begin(); it != currentRoom->triggers.end(); it++){
        if((!(*it)->check && first_check) && (*it)->evalConditions(*this)){
            evalAction((*it)->actions);
            evalPrint((*it)->printOuts);
            if(first_check){ (*it)->check = true; }
            else{ (*it)->check = false; }
            actionDone = true;
        }
        else{
            (*it)->check = false;
        }
    }
    
    for(itemIterator = currentRoom->itemObj.begin(); itemIterator != currentRoom->itemObj.end(); itemIterator++){
        //cout << "checkItemTriggers" << endl;
        Item * i = itemIterator->second;
        for(it = i->triggers.begin(); it != i->triggers.end(); it++){
            if((!(*it)->check && first_check) && (*it)->evalConditions(*this)){
                evalAction((*it)->actions);
                evalPrint((*it)->printOuts);
                if(first_check){ (*it)->check = true; }
                else{ (*it)->check = false; }
                actionDone = true;
            }
            else{
                (*it)->check = false;
            }
        }
    }
    
    for(containerIterator = currentRoom->containerObj.begin(); containerIterator != currentRoom->containerObj.end(); containerIterator++){
        //cout << "checkContainerTriggers" << endl;
        for(it = (*containerIterator)->triggers.begin(); it != (*containerIterator)->triggers.end(); it++){
            if((!(*it)->check && first_check) && (*it)->evalConditions(*this)){
                evalAction((*it)->actions);
                evalPrint((*it)->printOuts);
                if(first_check){ (*it)->check = true; }
                else{ (*it)->check = false; }
                actionDone = true;
            }
            else{
                (*it)->check = false;
            }
        }
    }
    
    for(creatureIterator = currentRoom->creatureObj.begin(); creatureIterator != currentRoom->creatureObj.end(); creatureIterator++){
        for(it = (*creatureIterator)->triggers.begin(); it != (*creatureIterator)->triggers.end(); it++){
            if((!(*it)->check && first_check) && (*it)->evalConditions(*this)){
                evalAction((*it)->actions);
                evalPrint((*it)->printOuts);
                if(first_check){ (*it)->check = true; }
                else{ (*it)->check = false; }
                actionDone = true;
            }
            else{
                (*it)->check = false;
            }
        }
    }
    
    //for itemIterator, for triggers in item, check trigger
    return actionDone;
}

void Zork::evalPrint(vector<string> print){
    vector<string>::iterator it;
    for(it = print.begin(); it != print.end(); it++){
        cout << (*it) << endl;
    }
}

void Zork::evalAction(vector<string> actions){
    vector<string>::iterator it;
    vector<string> actionList;
    for(it = actions.begin(); it != actions.end(); it++){
        cout << "Action: " << (*it) << endl;
        actionList = split(*it);
        if(actionList[0].compare("take") == 0){

            bool isItem = false;
            
            vector<Item*>::iterator itemIterator;
            for(itemIterator = itemObjs.begin(); itemIterator != itemObjs.end(); itemIterator++){
                if((*itemIterator)->name.compare(actionList[1]) == 0){
                    isItem = true;
                    cout << "Item added to inventory: " << actionList[1] << endl;
                    inventory[(*itemIterator)->name] = (*itemIterator);
                }
            }
            if(isItem == false){
                cout << "Item not found." << endl;
            }
            
        }
        else if(actionList[0].compare("attack") == 0){
            bool isCreature = false;
            
            vector<Creature*>::iterator cIt;
            for(cIt = creatureObjs.begin(); cIt != creatureObjs.end(); cIt++){
                if((*cIt)->name.compare(actionList[1]) == 0){
                    isCreature = true;
                    cout << "You assault the "<< actionList[1] << "with" << actionList[4] << endl;
                    //Creature -> attack(Item *) ? lmao
                    
                }
            }
            if(isCreature == false){
                cout << "Creature not found." << endl;
            }
        }
        else if(actionList[0].compare("Delete") == 0){
            bool isItem = false;
            
            vector<Item*>::iterator iIt;
            for(iIt = itemObjs.begin(); iIt != itemObjs.end(); iIt++){
                if((*iIt)->name.compare(actionList[1]) == 0){
                    isItem = true;
                    cout << "Removed " << actionList[1] << endl;
                }
            }
            if(isItem == false){
                cout << "Item not found." << endl;
            }
        }
        else if(actionList[0].compare("Add") == 0){
            bool isRoom = roomObjs.find(actionList[3]) != roomObjs.end();
            bool isContainer = containerObjs.find(actionList[3]) != containerObjs.end();
            
            
            vector<Item*>::iterator itemIterator;
            for(itemIterator = itemObjs.begin(); itemIterator != itemObjs.end(); itemIterator++){
                if((*itemIterator)->name.compare(actionList[1]) == 0){
                    if(isContainer){
                        Container *c = containerObjs.find(actionList[3])->second;
                        c->items[(*itemIterator)->name] = (*itemIterator);
                        cout << "Item " <<actionList[1]<< " was added to container " << actionList[3] << endl;
                    }
                    if(isRoom){
                        Room *r = roomObjs.find(actionList[3])->second;
                        r->itemObj[(*itemIterator)->name] = (*itemIterator);
                        cout << "Item " <<actionList[1]<< " was added to Room " << actionList[3] << endl;
                    }
                    
                }
            }
            vector<Creature*>::iterator cIt;
            for(cIt= creatureObjs.begin(); cIt != creatureObjs.end(); cIt++){
                if((*cIt)->name.compare(actionList[1]) == 0){
                    if(isRoom){
                        Room *r = roomObjs.find(actionList[3])->second;
                        r->creatureObj.push_back(*cIt);
                        cout << "Creature " << actionList[1] << " was added to Room " << actionList[3] << endl;
                    }
                }
            }
        }
        else if(actionList[0].compare("Update") == 0){
            bool isGameObject = gameObjects.find(actionList[1]) != gameObjects.end();
            if(isGameObject){
                
                GameObject *g = gameObjects.find(actionList[1])->second;
                g->status = actionList[3];
                cout << "Game Object: " << actionList[1] << " updated to: "<< actionList[3] << endl;
            }
        }
        else if(actionList[0].compare("Game") == 0){
            if(actionList[1].compare("Over") == 0){
                //game over
                cout << "Game over bitches" << endl;
            }
        }
        
        
    }
}

bool Zork::evalInput(string s, string prevS){
    
    bool valid = false;
    
    /* * * * * * * * * * * * * * * * * *  HELP  * * * * * * * * * * * * * * * * * */
    if(s == "help"){
        cout << endl;
        cout << "∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆∆\n"
        "----------------------------- LIST OF ZORK COMMANDS -----------------------------\n"
        "∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇∇\n\n"
        "[n,s,e,w] - Movement commands\n"
        "[i] - Shows the player's inventory\n"
        "[take] (item) - Allows a user to take an item from an inventory\n"
        "[open] (container) - Prints the contents of the container\n"
        "[read] (item) - Prints whatever is written on an object\n"
        //"[drop] (tim) - Drops Tim Dotson from Beta Theta Pi\n"
        "[drop] (item) - Drop item from inventory into current rooom\n"
        "[put] (item) in (container) - Adds the item to the conatiner's inventory\n"
        "[turn on] (item) - Activates item\n"
        "[attack] (creature) with (item) - Pretty self explanatory, it will do as it says\n"
        ""<< endl;
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  NORTH  * * * * * * * * * * * * * * * * * */
    if(s == "n" | s == "north"){
        string nextRoom;
        if(currentRoom->borders.find("north") != currentRoom->borders.end()){
            nextRoom = currentRoom->borders["north"];
            cout << endl << "Going to room: " << nextRoom << endl;
            Room * r = roomObjs.find(nextRoom)->second;
            currentRoom = r;
            currentRoom->printDescription();
        }
        else{
            cout << endl << "Can not go this way" << endl;
        }
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  SOUTH  * * * * * * * * * * * * * * * * * */
    if(s == "s" | s == "south"){
        string nextRoom;
        if(currentRoom->borders.find("south") != currentRoom->borders.end()){
            nextRoom = currentRoom->borders["south"];
            cout << endl << "Going to room: " << nextRoom << endl;
            Room * r = roomObjs.find(nextRoom)->second;
            currentRoom = r;
            currentRoom->printDescription();
        }
        else{
            cout << endl << "Can not go this way" << endl;
        }
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  EAST  * * * * * * * * * * * * * * * * * */
    if(s == "e" | s == "east"){
        string nextRoom;
        if(currentRoom->borders.find("east") != currentRoom->borders.end()){
            nextRoom = currentRoom->borders["east"];
            cout << endl << "Going to room: " << nextRoom << endl;
            Room * r = roomObjs.find(nextRoom)->second;
            currentRoom = r;
            currentRoom->printDescription();
        }
        else{
            cout << endl << "Can not go this way" << endl;
        }
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  WEST  * * * * * * * * * * * * * * * * * */
    if(s == "w" | s == "west"){
        string nextRoom;
        if(currentRoom->borders.find("west") != currentRoom->borders.end()){
            nextRoom = currentRoom->borders["west"];
            cout << endl << "Going to room: " << nextRoom << endl;
            Room * r = roomObjs.find(nextRoom)->second;
            currentRoom = r;
            currentRoom->printDescription();
        }
        else{
            cout << endl << "Can not go this way" << endl;
        }
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * *  INVENTORY  * * * * * * * * * * * * * * * * */
    if(s == "i"){
        printInventory();
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  TAKE  * * * * * * * * * * * * * * * * * */
    if(prevS == "take"){
        valid = takeObj(s);
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  OPEN  * * * * * * * * * * * * * * * * * */
    if(prevS == "open"){
        for(auto &i : currentRoom->containerObj){
            if(i->name == s){
                i->printContainer();
            }
        }
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  READ  * * * * * * * * * * * * * * * * * */
    if(prevS == "read"){
        
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    
    
    /* * * * * * * * * * * * * * * * * *  QUIT  * * * * * * * * * * * * * * * * * */
    if(s == "quit" || s == "end"){
        valid = true;
    }
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    return valid;
}

void Zork::parseAction(string){
    
}

bool Zork::takeObj(string s){
    bool valid = false;
    for(auto &i : currentRoom->itemObj){
            if(i.second->name == s){
                inventory[i.second->name] = i.second;
                cout << endl << i.second->name << " was added to your inventory" << endl;
                valid = true;
                return valid;
            }
    }

    for(auto &i : currentRoom->containerObj){
        map<string,Item *>::iterator it;
        for(it = i->items.begin(); it != i->items.end(); it++){
            if((*it).second->name == s){
                inventory[(*it).second->name] = (*it).second;
                cout << endl << (*it).second->name << " was added to your inventory" << endl;
                valid = true;
                return valid;
            }
        }
    }
    return valid;
}

void Zork::loadCurrentRoom(Room * room){
    cout << room->description << endl << endl;
}

/* James */
void Zork::printInventory(void){
    map<string, Item *>::iterator it;
    cout << endl << "Inventory:" << endl;
    for(it = inventory.begin(); it != inventory.end(); it++){
        cout << "   " << (it->second)->name << endl;
    }
}
