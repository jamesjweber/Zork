/*
 * StatusCondition.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: millerev
 */

#include "StatusCondition.h"
#include "Zork.h"

StatusCondition::StatusCondition() {
	// TODO Auto-generated constructor stub

}
StatusCondition::StatusCondition(xml_node<>* statusNode) {
	// TODO Auto-generated constructor stub
	xml_node<>* node;

	for(node = statusNode->first_node(); node; node = node->next_sibling()){
        string tag = node->name();
        if(tag.compare("object") == 0){
        	gameObject = node->value();
            //cout << "Status Condition Object: " << node->value() << endl;
        }
        else if(tag.compare("status") == 0){
        	status = node->value();
            //cout << "Status Condition Status: " << node->value() << endl;
        }
	}
}
StatusCondition::~StatusCondition() {
	// TODO Auto-generated destructor stub
}
bool StatusCondition::eval(Zork& z){
    //cout << "EVAL STATUS CONDITION" << endl;
    //cout << "Game Object: " << gameObject << endl;
    GameObject * g;
    if(z.gameObjects.find(gameObject) == z.gameObjects.end()){
        //cout << "FALSE - GAME OBJECT NOT FOUND" << endl;
        return false;
    }
    else {
        g = z.gameObjects.find(gameObject)->second;
    }
    //cout << "check: " << check << endl;
    
    //cout << z.gameObjects.find(gameObject)->second << endl;
    //cout << g->status << ":" << status << endl;
    if(g->status.compare(status) == 0){
        //cout << "EVAL TRUE - " << status << endl;
        return true;
	}
	else{
        //cout << "EVAL FALSE" << endl;
        return false;
	}
    return false;

}

