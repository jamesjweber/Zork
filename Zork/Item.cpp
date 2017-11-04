/*
 * Item.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: Evan Miller
 */

#include "Item.h"

Item::Item() {
	// TODO Auto-generated constructor stub

}
Item::Item(xml_node<>* itemNode){

	xml_node<>* node = itemNode->first_node();
		for(node = itemNode->first_node(); node; node = node->next_sibling){
			if(node->name() == "name"){}
			else if(node->name() == "status"){}
			else if(node->name() == "writing"){}
			else if(node->name() == "turnon"){}

		}
}

Item::~Item() {
	// TODO Auto-generated destructor stub
}
void setUp(xml_node<> *){


}
void turnOn(xml_node<> *){

}


