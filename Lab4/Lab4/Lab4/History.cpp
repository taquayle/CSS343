/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		History.cpp													*/
/*	PARENT:		Command														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "History.h"

History::History()
{
}
History::History(int accNum) : 
	Command(accNum, "D", "N")
{
}
History::History(int accNum, std::string medType, std::string movType) : 
	Command(accNum, medType, movType)
{
}


History::~History()
{
}


bool History::executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*> &movieDB)
{
	Customer *curCustomer;
	int tempAcc = getAccountNumber();
	bool foundCust = false;
	for (int i = 0; i < custDB.size(); i++)
	{
		if (tempAcc == custDB[i]->getAccountNumber())
		{
			curCustomer = custDB[i];
			foundCust = true;
		}
	}
	 if(foundCust)
	 {
 		curCustomer->showHistory();
		return true;
	 }
	 std::cerr << "ERROR: History, Invalid Account Number: " << tempAcc << " does not exsist\n";
	return false;
}
