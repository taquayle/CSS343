#pragma once
#include "Return.h"

class ReturnDrama : public Return
{
public:
	ReturnDrama();
	ReturnDrama(int accNum, std::string medType, std::ifstream &inFile);
	~ReturnDrama();

	// Inherited via Return
	virtual bool buildCommand(std::ifstream &inFile);
	virtual bool executeCommand(std::vector<Customer*>&, std::vector<Movie*>&);
	virtual std::string toString();
private:
	std::string movieTitle;
	std::string director;
};

