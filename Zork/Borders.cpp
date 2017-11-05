/*
 * Borders.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: Evan Miller
 */

#include "Borders.h"
using namespace std;

Borders::Borders() {
	// TODO Auto-generated constructor stub

}

Borders::~Borders() {
	// TODO Auto-generated destructor stub
}
Borders::Borders(xml_node<>* borderNode){

	//Note: A border node should have children of direction and name tags
	xml_node<>* node;

	for(node = borderNode->first_node(); node; node->next_sibling()){
		borders[node->first_node("direction")->value()] = node->first_node("name")->value();
	}

}
void Borders::printBorders(){

	//Note: An iterator is used to traverse the vector of borders
	for (std::map<string,string>::iterator it=borders.begin(); it!=borders.end(); ++it){
		cout<< it->first << " : " << it->second << endl;
	}

}

