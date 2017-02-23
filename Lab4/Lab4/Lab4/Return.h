#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Return.h													*/
/*	PARENT:		Command														*/
/*	CHILDREN:	ReturnClassic, ReturnComedy, ReturnDrama					*/
/****************************************************************************/
#include "Command.h"
class Return : public Command
{
protected:
	Return(int accNum, std::string medType, std::string movType);

	virtual bool buildCommand(std::ifstream &inFile) = 0;
	virtual std::string toString() = 0;
public:
	Return();
	virtual ~Return();

	// Inherited via Command
	virtual bool executeCommand(std::vector<Customer*> &, std::vector<Movie*> &) =0;
};