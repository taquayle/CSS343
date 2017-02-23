#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		BorrowDrama.h												*/
/*	PARENT:		Borrow														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Borrow.h"
class BorrowDrama : public Borrow
{
public:
	BorrowDrama();
	~BorrowDrama();
	BorrowDrama(int accNum, std::string medType, std::ifstream &inFile);

	// Inherited via Return
	virtual bool buildCommand(std::ifstream &inFile);
	virtual bool executeCommand(std::vector<Customer*>&, std::vector<Movie*>&);
	virtual std::string toString();
private:
	std::string movieTitle;
	std::string director;
};

