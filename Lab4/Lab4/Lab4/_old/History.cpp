#include "History.h"



History::History()
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
	curCustomer->showHistory();
	return false;
}
