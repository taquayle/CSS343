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
	for (int i = 0; i < movieDB.size(); i++)
	{
		std::cout << *movieDB[i];
	}
	std::cout << std::endl << "Total Movies: " << movieDB.size() << std::endl;
	return false;
}
