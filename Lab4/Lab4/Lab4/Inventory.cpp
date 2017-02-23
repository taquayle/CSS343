/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Inventory.cpp												*/
/*	PARENT:		Command														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Inventory.h"
#include <vector>

Inventory::Inventory()
{
}

Inventory::Inventory(int accNum, std::string medType, std::string movType) : Command(accNum, medType,movType)
{
}


Inventory::~Inventory()
{
}

bool Inventory::executeCommand(std::vector<Customer*> &customerDB, std::vector<Movie*> &movieDB)
{	
	std::cout << "\n--- INVENTORY ---\n";
	for (int i = 0; i < movieDB.size(); i++)
	{
		std::cout << *movieDB[i];
	}
	return false;
}