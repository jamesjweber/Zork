/*
 * Command.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: millerev
 */

#include "Command.h"
#include "Zork.h"

Command::Command() {
	// TODO Auto-generated constructor stub

}
Command::Command(xml_node<>* commandNode){
	command = commandNode->value();
}

Command::~Command() {
	// TODO Auto-generated destructor stub

}

bool Command::eval(Zork &z){
	if(command.empty() or command.compare(z.userInput) == 0){
		return true;
	}
	else{
		return false;
	}

}
