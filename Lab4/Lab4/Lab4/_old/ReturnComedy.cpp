#include "ReturnComedy.h"



ReturnComedy::ReturnComedy()
{
}

ReturnComedy::ReturnComedy(int accNum, std::string medType, std::ifstream & inFile) : Return(accNum, medType, "F")
{
	buildCommand(inFile);
}


ReturnComedy::~ReturnComedy()
{
}

bool ReturnComedy::buildCommand(std::ifstream & inFile)
{
	std::getline(inFile, movieTitle, ',');
	inFile >> releaseYear;
	return false;
}

bool ReturnComedy::executeCommand(std::vector<Customer*> &custDB, std::vector<Movie*> &movieDB)
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

			if (movieTitle == movieDB[i]->getTitle())
			{
				if (releaseYear == movieDB[i]->getReleaseYear())
				{
					curMovie = movieDB[i];
					foundMovie = true;
				}
			}
		}
		if (foundMovie)
		{
			curMovie->returnMovie();
			curCustomer->addHistory(toString());
		}
	}
	return false;
}


std::string ReturnComedy::toString()
{
	std::string retVal;
	retVal.append("R " + std::to_string(getAccountNumber()));
	retVal.append(" " + getMediaType());
	retVal.append(" " + getMovieType());
	retVal.append(" " + movieTitle);
	retVal.append(", " + std::to_string(releaseYear));
	return retVal;
}
