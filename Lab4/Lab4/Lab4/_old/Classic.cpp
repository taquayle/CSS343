#include "Classic.h"

Classic::Classic()
{
	releaseMonth = -1;
	releaseYear = -1;
}

Classic::Classic(std::ifstream & inFile)
{
	getMovie(inFile);
}

Classic::Classic(int relYear, int relMonth, int _stock, std::string actFirst, std::string actLast, std::string dirFirst, std::string dirLast, std::string _title) : Movie(relYear, _stock, dirFirst, dirLast, _title)
{
	actors.push_back(actFirst + " " + actLast);
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


void Classic::setActor(std::string actFirst, std::string actLast)
{
	actors.push_back(actFirst + " " + actLast);
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

void Classic::sameMovie(int _stock, std::string actFirst, std::string actLast)
{
	addStock(_stock);
	addActor(actFirst, actLast);
}

void Classic::addActor(std::string actFirst, std::string actLast)
{
	std::string newActor = actFirst + " " + actLast;
	actors.push_back(newActor);

	// ALPHABATIZE(SP?) ATTEMPT. DID NOT WORK
	/*std::string alphabeticalActor = actors[0];
	for (int i = 0; i <= actors.size(); i++)
	{
		if (newActor < actors[i])
		{
			std::string temp = actors[i];
			actors[i] = newActor;
		}
	}*/
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

void Classic::getMovie(std::ifstream & inFile)
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
	setActor(firName, lasName);
	inFile >> releaseMonth;
	inFile >> releaseYear;
	std::getline(inFile, temp);
}
