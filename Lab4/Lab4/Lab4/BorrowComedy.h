#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		BorrowComedy.h												*/
/*	PARENT:		Borrow														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Borrow.h"
class BorrowComedy : public Borrow
{
public:
	BorrowComedy();
	~BorrowComedy();
	BorrowComedy(int accNum, std::string medType, std::ifstream &inFile);

	// Inherited via Return
	virtual bool buildCommand(std::ifstream &inFile);
	virtual bool executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*>	&movieDB);
	virtual std::string toString();
private:
	std::string movieTitle;
	int releaseYear;
};

