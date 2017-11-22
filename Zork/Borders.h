/*
 * Borders.h
 *
 *  Created on: Nov 3, 2017
 *      Author: Evan Miller
 */

#ifndef BORDERS_H_
#define BORDERS_H_

#include "rapidxml.hpp"

#include <iostream>
#include <map>

using namespace std;
using namespace rapidxml;

class Borders {
public:
	Borders();
	Borders(xml_node<>* borderNode);
	virtual ~Borders();
	void printBorders();
	map<string, string> borders;
};

#endif /* BORDERS_H_ */
