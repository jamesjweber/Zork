/*
 * Zork.h
 *
 *  Created on: Nov 3, 2017
 *      Author: millerev
 */

#ifndef ZORK_H_
#define ZORK_H_

#include "rapidxml.hpp"

/*class Item;
class Containter;
class Trigger;
class Room;
class Creature; */

#include <list>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include "Room.h"
#include "GameObject.h"

using namespace std;
using namespace rapidxml;

class Zork {
public:
	Zork(string s);
	virtual ~Zork();

	string userInput;
	Room* currentRoom;
	map<string, Item*> inventory;
	/* map<string, Item*> inventory;
	map<string, Item*> items;
	map<string , Room*> rooms;
	map<string, Creature*> creatures;
	map<string, Trigger*> triggers; */

	xml_node<> * setUpGame(string s);
    void makeMap(xml_node<> * mapNode);
	void StartGame();
	void checkTriggers();
    bool evalInput(string, string);
    void parseAction(string);
    void getSibling(xml_node<>* root);
    void loadCurrentRoom(Room *);
    void getInput(void);
    void printInventory(void);


	Room* nodeToRoom(xml_node<>* roomNode);
	Item* nodeToItem(xml_node<>* itemNode);
	Creature* nodeToCreature(xml_node<>* creatureNode);
	Container* nodeToContainer(xml_node<>* containerNode);
	Trigger* nodeToTrigger(xml_node<>* tiggerNode);


    xml_node<> * mapNode;
    map<string, xml_node<> *> room_xml;
    map<string, xml_node<> *> item_xml;
    map<string, xml_node<> *> container_xml;
    map<string, xml_node<> *> creature_xml;
    //map<string, Room *> roomObj;
    list<string> inputs;
    list<Item *> inventry;

    map<string, GameObject*> gameObjects; //Map all game objects
    map<string, Room*> roomObjs;
    map<string, Container*> containerObjs;
    vector<Creature*> creatureObjs;
    vector<Item*> itemObjs;

};

#endif /* ZORK_H_ */
