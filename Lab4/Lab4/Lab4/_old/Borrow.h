#pragma once
#include "Command.h"

class Borrow : public Command
{
public:
	Borrow();
	~Borrow();
	// Inherited via Command
	virtual bool executeCommand(std::vector<Customer*> &, std::vector<Movie*> &);

private:


};