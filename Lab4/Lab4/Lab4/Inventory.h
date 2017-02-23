#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Inventory.h													*/
/*	PARENT:		Command														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Command.h"
class Inventory : public Command
{
public:
	Inventory();
	Inventory(int accNum, std::string medType, std::string movType);
	~Inventory();

	// Inherited via Command
	virtual bool executeCommand(std::vector<Customer*> &, std::vector<Movie*> &);

};

