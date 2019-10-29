/*
 * Trigger.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: millerev
 */

#include "Trigger.h"
#include "Zork.h"

using namespace std;

Trigger::Trigger() {
	// TODO Auto-generated constructor stub

}

Trigger::~Trigger() {
	// TODO Auto-generated destructor stub
}

Trigger::Trigger(xml_node<>* triggerNode){

	xml_node<>* node;
    check = false;
	for(node = triggerNode->first_node(); node; node = node->next_sibling()){
        string tag = node->name();

        if(tag.compare("command") == 0){
            Command * c  = new Command(node);
            conditions.push_back(c);
            
        }
        else if(tag.compare("condition") == 0){
        	//conditions.push_back(new Condition(node));
        	//Check the type of condition...
            //cout << "CONDITION FOUND" << endl;
            xml_node<>* cNode;
        	for(cNode = node->first_node(); cNode; cNode = cNode->next_sibling()){
        		string tag2 = cNode->name();
                //cout << tag2 << endl;
                if(tag2.compare("status") == 0){
                    //cout << "STATUS CONDITION" << endl;
                    StatusCondition* c = new StatusCondition(node);
        			conditions.push_back(c);
        			break;
        		}
        		else if(tag2.compare("has") == 0){
                    //cout << "OWNER CONDITION" << endl;
        			OwnerCondition* c = new OwnerCondition(node);
        			conditions.push_back(c);
        			break;
        		}
        	}
        }
        else if(tag.compare("action") == 0){
            cout << "@"<<node->value() << endl;
        	actions.push_back(node->value());
        }
        else if(tag.compare("print") == 0){
            cout <<"@"<<node->value() << endl;
        	printOuts.push_back(node->value());
        }

   }

}

bool Trigger::evalConditions(Zork &z){
    vector<Condition *>::iterator it;
    //cout << "TRIGGER DENISE" << endl;
    for(it = conditions.begin(); it != conditions.end(); it++){
        
        
                if((*it)->eval(z)){
                    //cout << "Condition met." << endl;
                    
                }
                else{
                    //One of the conditions is not met
                    //cout << "Conditions not met" << endl;
                    return false;
                }
            
    }
    //Print out messages
    
    //Perform actions
    //for each trigger...
    //if checkTrigger() then performAction(trigger.actions)
    return true;
}

