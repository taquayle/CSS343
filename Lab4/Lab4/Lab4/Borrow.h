#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Borrow.h													*/
/*	PARENT:		Command														*/
/*	CHILDREN:	BorrowComedy, BorrowDrama, BorrowClassic					*/
/****************************************************************************/
#include "Command.h"
class Borrow : public Command
{
protected:
	Borrow(int accNum, std::string medType, std::string movType);

	virtual bool buildCommand(std::ifstream &inFile) = 0;
	virtual std::string toString() = 0;
public:
	Borrow();
	virtual ~Borrow();
	// Inherited via Command
	virtual bool executeCommand(std::vector<Customer*> &, std::vector<Movie*> &);
};