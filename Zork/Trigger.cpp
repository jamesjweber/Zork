/*
 * Trigger.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: millerev
 */
 
#include "Trigger.h"

using namespace std;

Trigger::Trigger() {
	// TODO Auto-generated constructor stub

}

Trigger::~Trigger() {
	// TODO Auto-generated destructor stub
}

Trigger::Trigger(xml_node<>* triggerNode){

	xml_node<>* node;

	for(node = triggerNode->first_node(); node; node = node->next_sibling()){
        string tag = node->name();

        if(tag.compare("command") == 0){
        	commands.insert(node->value());
        }
        else if(tag.compare("condition") == 0){
        	conditions.push_back(new Condition(node));
        }
        else if(tag.compare("action") == 0){
        	actions.push_back(node->value());
        }
        else if(tag.compare("print") == 0){
        	printOuts.push_back(node->value());
        }
   }

}

bool Trigger::evalCommands(string input){
	//iterate through commands to match the input string
	if (commands.find(input) != commands.end()){
		return true;
	}
	else{
		return false;
	}
}
bool Trigger::evalConditions(){

	return true;

}

