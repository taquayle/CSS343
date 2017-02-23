#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		BorrowClassic.h												*/
/*	PARENT:		Borrow														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Borrow.h"
class BorrowClassic : public Borrow
{
public:
	BorrowClassic();
	BorrowClassic(int accNum, std::string medType, std::ifstream &inFile);
	~BorrowClassic();

	// Inherited via Return
	virtual bool buildCommand(std::ifstream &inFile);
	virtual bool executeCommand(std::vector<Customer*>&, std::vector<Movie*>&);
	virtual std::string toString();
private:
	std::string actor;
	int releaseMonth;
	int releaseYear;
};