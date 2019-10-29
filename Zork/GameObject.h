/*
 * GameObject.h
 *
 *  Created on: Nov 23, 2017
 *      Author: millerev
 */

#ifndef ZORK_GAMEOBJECT_H_
#define ZORK_GAMEOBJECT_H_

#include <vector>
#include <string>
#include "Trigger.h"

using namespace std;

class GameObject {
public:
	GameObject();
	string status;
	vector<Trigger*> triggers;

	virtual ~GameObject();
};

#endif /* ZORK_GAMEOBJECT_H_ */
