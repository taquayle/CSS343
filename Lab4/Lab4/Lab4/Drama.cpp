/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Drama.cpp													*/
/*	PARENT:		Movie														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Drama.h"
#include <string>

Drama::Drama()
{
}

Drama::Drama(std::ifstream & inFile)
{
	buildMovie(inFile);
}

Drama::Drama(int _year, int _stock, std::string dirFirst, std::string dirLast, std::string _title) : Movie(_year, _stock, dirFirst, dirLast, _title)
{
}


Drama::~Drama()
{
}

void Drama::print(std::ostream &indirect)
{
	indirect << "Drama - " << getStock()
				<< " - " << getDirector()
				<< " - " << getTitle()
				<< " - " << getReleaseYear()
				<< std::endl;
}

void Drama::buildMovie(std::ifstream & inFile)
{
	std::string temp;
	int tempYear;
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

	inFile >> tempYear;
	setReleaseYear(tempYear);

	std::getline(inFile, temp);
}
/* NEED THIS FOR VIRTUAL */
int Drama::getReleaseMonth() const
{
	return 0;
}
/* NEED THIS FOR VIRTUAL */
void Drama::setReleaseMonth(int relMonth)
{
}
/* NEED THIS FOR VIRTUAL */
bool Drama::checkCast(std::string actorCheck)
{
	return false;
}
