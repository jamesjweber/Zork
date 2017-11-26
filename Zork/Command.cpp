/*
 * Command.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: millerev
 */

#include "Command.h"

Command::Command() {
	// TODO Auto-generated constructor stub

}
Command::Command(xml_node<>* commandNode){
	command = commandNode->value();
}

Command::~Command() {
	// TODO Auto-generated destructor stub

}

bool Command::eval(string s){
	if(command.empty() or command.compare(s) == 0){
		return true;
	}
	else{
		return false;
	}

}
