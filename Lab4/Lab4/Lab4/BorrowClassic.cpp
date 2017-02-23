/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		BorrowClassic.cpp											*/
/*	PARENT:		Borrow														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "BorrowClassic.h"



BorrowClassic::BorrowClassic()
{
}

BorrowClassic::BorrowClassic(int accNum, std::string medType, std::ifstream & inFile) : 
	Borrow(accNum, medType, "C")
{
	buildCommand(inFile);
}


BorrowClassic::~BorrowClassic()
{
}

bool BorrowClassic::buildCommand(std::ifstream & inFile)
{
	std::string actFirst;
	std::string actLast;
	inFile >> releaseMonth;
	inFile >> releaseYear;
	inFile >> actFirst;
	inFile >> actLast;
	actor = actFirst + " " + actLast;

	std::string temp;
	std::getline(inFile, temp);
	return false;
}

bool BorrowClassic::executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*> &movieDB)
{
	Customer *curCustomer;
	Movie *curMovie;
	int tempAcc = getAccountNumber();
	bool foundMovie = false;
	bool foundCust = false;

	for (int i = 0; i < custDB.size(); i++)
	{
		if (tempAcc == custDB[i]->getAccountNumber())
		{
			curCustomer = custDB[i];
			foundCust = true;
		}
	}
	if (foundCust == true)
	{
		for (int i = 0; i < movieDB.size(); i++)
		{
			if (releaseMonth == movieDB[i]->getReleaseMonth())
			{
				if (releaseYear == movieDB[i]->getReleaseYear())
				{
					if (movieDB[i]->checkCast(actor))
					{
						curMovie = movieDB[i];
						foundMovie = true;
					}
				}
			}
		}
		if (foundMovie)
		{
			if (curMovie->borrowMovie())
			{
				curCustomer->addHistory(toString());
				return true;
			}
			std::cerr << "ERROR: No More Copies of - Actor:" << actor << " - Release Date:" << releaseMonth << " " << releaseYear << " \n";
			return false;
		}
		std::cerr << "ERROR: Movie Does Not exist - Actor:" << actor << " - Release Date:" << releaseMonth << " " << releaseYear <<" \n";
		return false;
	}
	std::cerr << "ERROR: Invalid Account Number: " << tempAcc << " does not exsist\n";
	return false;
}

std::string BorrowClassic::toString()
{
	std::string intToString;
	std::stringstream its;
	its << getAccountNumber();
	intToString = its.str();
	its.str(std::string());
	std::string retVal;
	retVal.append("B " + intToString);
	retVal.append(" " + getMediaType());
	retVal.append(" " + getMovieType());

	its << releaseMonth;
	intToString = its.str();
	its.str(std::string());
	retVal.append(" " + intToString);

	its << releaseYear;
	intToString = its.str();
	retVal.append(" " + intToString);
	retVal.append(" " + actor);
	return retVal;
}