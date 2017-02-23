#pragma once
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

