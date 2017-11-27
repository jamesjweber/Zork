/*
 * Container.cpp
 *
 *  Created on: Nov 4, 2017
 *      Author: millerev
 */

#include "Container.h"
#include "Item.h"
#include <iostream>

using namespace std;

Container::Container() {
	// TODO Auto-generated constructor stub

}

Container::~Container() {
	// TODO Auto-generated destructor stub
}

bool Container::hasItem(string item){
	return false;
}
void Container::checkTriggers(){

}
void Container::checkAccept(){

}

void Container::printContainer(){
    map<string,Item *>::iterator it;
    cout << endl << name << " contents:" << endl;
    for(it = items.begin(); it != items.end(); it++){
        cout << "   " << it->second->name << endl;
    }
    cout << "----------------" << endl;
}

