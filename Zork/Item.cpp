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

	xml_node<>* node;
		for(node = itemNode->first_node(); node; node = node->next_sibling())
		{
			string tag = node->name();
	        if(tag.compare("name") == 0){
	        	name = node->value();
	        }
			else if(tag.compare("writing") == 0){
				writing = node->value();
			}
			else if(tag.compare("status") == 0){
				status = node->value();
			}
			else if(tag.compare("description") == 0){
				description = node->value();
			}
	        else if(tag.compare("turnon") == 0){

	        }
	        else if(tag.compare("trigger") == 0){

	        }


		}
}

Item::~Item() {
	// TODO Auto-generated destructor stub
}
void Item::setUp(xml_node<> *){


}
void Item::turnOn(xml_node<> *){

}


