#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		ReturnComedy.h												*/
/*	PARENT:		Return														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Return.h"
class ReturnComedy : public Return
{
public:
	ReturnComedy();
	ReturnComedy(int accNum, std::string medType, std::ifstream &inFile);
	~ReturnComedy();

	// Inherited via Return
	virtual bool buildCommand(std::ifstream &inFile);
	virtual bool executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*>	&movieDB);
	virtual std::string toString();
private:
	std::string movieTitle;
	int releaseYear;
};

