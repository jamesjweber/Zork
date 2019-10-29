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
#include "StatusCondition.h"
#include "OwnerCondition.h"
#include "Command.h"

#include <vector>
#include <string>
#include <set>
using namespace rapidxml;
using namespace std;

class Zork;

class Trigger {
public:
	Trigger();
	Trigger(xml_node<>* triggerNode);
	virtual ~Trigger();
    
    bool check;
    
    
	vector<Condition *> conditions;

	vector<string> actions;
	vector<string> printOuts;

	bool evalConditions(Zork &z); //evaluate the conditions
	//void applyActions(string s); Apply actions of the trigger

};

 /* namespace std */

#endif /* ZORK_TRIGGER_H_ */
