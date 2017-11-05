//============================================================================
// Name        : zork.cpp
// Author      : Evan Miller
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "zork.h"
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
    }
}
void checkTriggers(){}
void evalInput(string){}
void parseAction(string){}

