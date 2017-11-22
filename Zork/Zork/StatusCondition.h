/*
 * StatusCondition.h
 *
 *  Created on: Nov 20, 2017
 *      Author: millerev
 */

#ifndef ZORK_STATUSCONDITION_H_
#define ZORK_STATUSCONDITION_H_

#include <string>
#include "Condition.h"

class StatusCondition : public Condition {
public:
	StatusCondition();
	virtual ~StatusCondition();
	string itemName;
	string status;
};

#endif /* ZORK_STATUSCONDITION_H_ */
