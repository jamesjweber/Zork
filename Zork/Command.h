/*
 * Command.h
 *
 *  Created on: Nov 11, 2017
 *      Author: millerev
 */

#ifndef ZORK_COMMAND_H_
#define ZORK_COMMAND_H_

#include "rapidxml.hpp"
#include "Condition.h"
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using namespace rapidxml;

class Zork;

class Command : public Condition {
public:
	Command();
	Command(xml_node<>* commandNode);
	string command;
	virtual ~Command();
	virtual bool eval(Zork &z);
};

#endif /* ZORK_COMMAND_H_ */
