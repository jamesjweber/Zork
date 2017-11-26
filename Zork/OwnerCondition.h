/*
 * OwnerCondition.h
 *
 *  Created on: Nov 20, 2017
 *      Author: millerev
 */

#ifndef ZORK_OWNERCONDITION_H_
#define ZORK_OWNERCONDITION_H_

#include "Condition.h"
#include <iostream>

using namespace std;

class OwnerCondition: public Condition {
public:
	OwnerCondition();
	OwnerCondition(xml_node<>* ownerNode);
	virtual ~OwnerCondition();
	bool has;
	string owner;
	string object;
	bool eval(Zork&);
};

#endif /* ZORK_OWNERCONDITION_H_ */
