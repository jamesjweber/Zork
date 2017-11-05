/*
 * Container.cpp
 *
 *  Created on: Nov 4, 2017
 *      Author: millerev
 */

#include "Container.h"
#include "Item.h"
#include <iostream>

using namespace std;

Container::Container() {
	// TODO Auto-generated constructor stub

}
Container::Container(xml_node<>* containerNode){

	//string tag = containerNode->name();
	xml_node<>* child = containerNode->first_node();

	for(; child; child = child->next_sibling()){
		string tag = child->name();
		if(tag.compare("name") == 0){
			name = child->value();
		}
		else if(tag.compare("description") == 0){
			description = child->value();
		}
		else if(tag.compare("status") == 0){
			description = child->value();
		}
		else if(tag.compare("accept") == 0){
			accepts.push_back(child->value());
		}
		else if(tag.compare("item") == 0){
			Item i = new Item(child);
			items.push_back(i);
		}
		else if(tag.compare("trigger") == 0){
			cout << "trigger lmao" << endl;
		}
	}
}
Container::~Container() {
	// TODO Auto-generated destructor stub
}

bool Container::hasItem(string item){
	return false;
}
void Container::checkTriggers(){

}
void Container::checkAccept(){

}
