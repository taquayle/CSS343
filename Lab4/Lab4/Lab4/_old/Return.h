#pragma once
#include "Command.h"
class Return : public Command
{
protected:
	Return(int accNum, std::string medType, std::string movType);

	virtual bool buildCommand(std::ifstream &inFile) = 0;
	virtual std::string toString() = 0;
public:
	Return();
	~Return();

	// Inherited via Command
	virtual bool executeCommand(std::vector<Customer*> &, std::vector<Movie*> &) =0;
};