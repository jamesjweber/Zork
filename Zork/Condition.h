/*
 * Condition.h
 *
 *  Created on: Nov 11, 2017
 *      Author: millerev
 */

#ifndef ZORK_CONDITION_H_
#define ZORK_CONDITION_H_

#include "rapidxml.hpp"
#include <map>
#include <string>
//#include "Zork.h"

using namespace rapidxml;
using namespace std;

class Zork;

class Condition {
public:
	Condition();
	Condition(xml_node<>* conditionNode);
	string s = "";

	virtual ~Condition();
	virtual bool eval(Zork& z) = 0;
};

#endif /* ZORK_CONDITION_H_ */
