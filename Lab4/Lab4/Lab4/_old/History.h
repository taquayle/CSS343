#pragma once
#include "Command.h"
class History : public Command
{
public:
	History();
	History(int accNum, std::string medType, std::string movType);
	~History();

	// Inherited via Command
	virtual bool executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*> &movieDB);
};

