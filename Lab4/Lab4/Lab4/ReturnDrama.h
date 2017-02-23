#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		ReturnDrama.h												*/
/*	PARENT:		Return														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
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

