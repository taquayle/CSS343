#pragma once
#include "Return.h"
class ReturnClassic : public Return
{
public:
	ReturnClassic();
	ReturnClassic(int accNum, std::string medType, std::ifstream &inFile);
	~ReturnClassic();

	// Inherited via Return
	virtual bool buildCommand(std::ifstream &inFile);
	virtual bool executeCommand(std::vector<Customer*>&, std::vector<Movie*>&);
	virtual std::string toString();
private:
	std::string actor;
	int releaseMonth;
	int releaseYear;
};