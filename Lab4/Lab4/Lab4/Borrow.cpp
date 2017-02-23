/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Borrow.cpp													*/
/*	PARENT:		Command														*/
/*	CHILDREN:	BorrowDrama, BorrowComedy, BorrowClassic					*/
/****************************************************************************/
#include "Borrow.h"



Borrow::Borrow(int accNum, std::string medType, std::string movType):
	Command(accNum, medType, movType)
{
}

Borrow::Borrow()
{
}


Borrow::~Borrow()
{
}


bool Borrow::executeCommand(std::vector<Customer*> &, std::vector<Movie*> &)
{
	return false;
}
