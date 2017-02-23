/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Classic.cpp													*/
/*	PARENT:		Movie														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Classic.h"

Classic::Classic()
{
	releaseMonth = -1;
	releaseYear = -1;
}

Classic::Classic(std::ifstream & inFile)
{
	buildMovie(inFile);
}

Classic::Classic(int relYear, int relMonth, int _stock, std::string _actor, std::string dirFirst, std::string dirLast, std::string _title) : Movie(relYear, _stock, dirFirst, dirLast, _title)
{
	actors.push_back(_actor);
	releaseMonth = relMonth;
}

Classic::~Classic()
{
  std::vector<std::string>().swap(actors);
}

int Classic::getReleaseMonth() const
{
	return releaseMonth;
}

void Classic::setReleaseMonth(int relMonth)
{
	releaseMonth = relMonth;
}


void Classic::setActor(std::string _actor)
{
	actors.push_back(_actor);
}

std::string Classic::getMainAct() const
{
	return actors[0];
}

void Classic::getActors(std::ostream &actorOut) const
{
	for (int i = 0; i < actors.size(); i++)
	{
		actorOut << actors[i] << "";
	}
}

bool Classic::checkCast(std::string actorCheck)
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (actorCheck == actors[i])
		{
			return true;
		}
	}
	return false;
}

void Classic::sameMovie(int _stock, std::string _actor)
{
	addStock(_stock);
	addActor(_actor);
}

void Classic::addActor(std::string _actor)
{
	actors.push_back(_actor);
}

void Classic::addStock(int _stock)
{
	setStock(getStock() + _stock);
}

void Classic::print(std::ostream & indirect)
{
	indirect << "Classic - " << getStock()
		<< " - " << getDirector()
		<< " -" << getTitle()
		<< " - ";
	
	getActors(indirect);
	
	indirect << " - " << getReleaseMonth()
		<< " " << getReleaseYear()
		<< std::endl;
}

void Classic::buildMovie(std::ifstream & inFile)
{
	std::string temp;
	std::string firName;
	std::string lasName;
	std::string clear;

	/* Get Stock */
	std::getline(inFile, temp, ',');
	setStock(std::atoi(temp.c_str()));

	/* Get Director name */
	std::getline(inFile, temp, ',');	// Get Full Name to comma
	std::istringstream dirName(temp);	// Put in string stream 
	dirName >> firName;	// dirName[1] = First Name
	dirName >> lasName;		// dirName[2] = Last name
	while (dirName.good())	// If last name has a split. eg De Broca
	{
		std::string temp = lasName;
		dirName >> lasName;
		temp.append(" ");
		temp.append(lasName);
		lasName = temp;
	}
	setDirector(firName, lasName);

	/* Get Movie Title*/
	std::getline(inFile, temp, ',');
	setTitle(temp);

	inFile >> firName;
	inFile >> lasName;
	setActor(firName + " " + lasName);
	inFile >> releaseMonth;
	inFile >> releaseYear;

	/* CLEAR REST OF LINE */
	std::getline(inFile, temp);
}
