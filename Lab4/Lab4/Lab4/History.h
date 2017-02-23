#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		History.h													*/
/*	PARENT:		Command														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Command.h"
class History : public Command
{
public:
	History();
  History(int accNum);
	History(int accNum, std::string medType, std::string movType);
	~History();

	// Inherited via Command
	virtual bool executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*> &movieDB);
};

