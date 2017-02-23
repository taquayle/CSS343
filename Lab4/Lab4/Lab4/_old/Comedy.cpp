#include "Comedy.h"


Comedy::Comedy()
{
}

Comedy::Comedy(std::ifstream & inFile)
{
	getMovie(inFile);
}

Comedy::Comedy(int _year, int _stock, std::string dirFirst, std::string dirLast, std::string _title) : Movie(_year, _stock, dirFirst, dirLast, _title)
{
}

Comedy::~Comedy()
{
}

void Comedy::print(std::ostream & indirect)
{
	indirect << "Comedy - " << getStock()
		<< " - " << getDirector()
		<< " - " << getTitle()
		<< " - " << getReleaseYear()
		<< std::endl;
}

void Comedy::getMovie(std::ifstream & inFile)
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
int Comedy::getReleaseMonth() const
{
	return 0;
}
/* NEED THIS FOR VIRTUAL */
void Comedy::setReleaseMonth(int relMonth)
{
}
/* NEED THIS FOR VIRTUAL */
bool Comedy::checkCast(std::string actorCheck)
{
	return false;
}
