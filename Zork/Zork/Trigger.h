/*
 * Trigger.h
 *
 *  Created on: Nov 11, 2017
 *      Author: millerev
 */

#ifndef ZORK_TRIGGER_H_
#define ZORK_TRIGGER_H_

#include "rapidxml.hpp"
#include "Condition.h"
#include "Command.h"

#include <vector>
#include <string>
#include <set>
using namespace rapidxml;
using namespace std;

class Trigger {
public:
	Trigger();
	Trigger(xml_node<>* triggerNode);
	virtual ~Trigger();
	vector<Condition *> conditions;
	set<string> commands;
	vector<string> actions;
	vector<string> printOuts;

	bool evalCommands(string input); //check for a valid commands
	bool evalConditions(); //evaluate the conditions
	//void applyActions(string s); Apply actions of the trigger

};

 /* namespace std */

#endif /* ZORK_TRIGGER_H_ */
