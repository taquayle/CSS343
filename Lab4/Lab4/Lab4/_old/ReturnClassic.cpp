#include "ReturnClassic.h"



ReturnClassic::ReturnClassic()
{
}

ReturnClassic::ReturnClassic(int accNum, std::string medType, std::ifstream & inFile): Return(accNum, medType, "C")
{
	buildCommand(inFile);
}


ReturnClassic::~ReturnClassic()
{
}

bool ReturnClassic::buildCommand(std::ifstream &inFile)
{
	std::string actFirst;
	std::string actLast;
	inFile >> releaseMonth;
	inFile >> releaseYear;
	inFile >> actFirst;
	inFile >> actLast;
	actor = actFirst + " " + actLast;
	return false;
}

bool ReturnClassic::executeCommand(std::vector<Customer*>&custDB, std::vector<Movie*>&movieDB)
{
	Customer *curCustomer;
	Movie *curMovie;
	int tempAcc = Return::getAccountNumber();
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
		/*************************CLASSIC*************************************/
		if (Return::getMovieType() == "C")
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
				curMovie->returnMovie();
				curCustomer->addHistory(toString());
			}
		}
	}
	return false;
}

std::string ReturnClassic::toString()
{
	std::string retVal;
	retVal.append("R " + std::to_string(getAccountNumber()));
	retVal.append(" " + getMediaType());
	retVal.append(" " + getMovieType());
	retVal.append(" " + std::to_string(releaseMonth));
	retVal.append(" " + std::to_string(releaseYear));
	retVal.append(" " + actor);
	return retVal;
}
