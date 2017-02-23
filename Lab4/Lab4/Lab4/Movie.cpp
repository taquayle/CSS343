/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Movie.cpp													*/
/*	PARENT:		NONE														*/
/*	CHILDREN:	Drama, Comedy, Classic										*/
/****************************************************************************/
#include "Movie.h"

Movie::Movie()
{
	stock = -1;
	intialStock = -1;
	releaseYear = -1;
	directFirst = "N/A";
	directLast = "N/A";
	title = "N/A";
}

Movie::Movie(int _year, int _stock, std::string dirFirst, std::string dirLast, std::string _title)
{
	releaseYear = _year;
	stock = _stock;
	intialStock = stock;
	directFirst = dirFirst;
	directLast = dirLast;
	title = _title;
}


Movie::~Movie()
{
}

std::string Movie::getTitle() const
{
	return title;
}

void Movie::setTitle(std::string _title)
{
	title = _title;
}

std::string Movie::getDirector() const
{
	std::string temp = directFirst + " " + directLast;
	return temp;
}

void Movie::setDirector(std::string dirFirst, std::string dirLast)
{
	directFirst = dirFirst;
	directLast = dirLast;
}

int Movie::getStock() const
{
	return stock;
}

void Movie::setStock(int _stock)
{
	stock = _stock;
	intialStock = stock;
}

int Movie::getReleaseYear() const
{
	return releaseYear;
}

void Movie::setReleaseYear(int _year)
{
	releaseYear = _year;
}

bool Movie::borrowMovie()
{
	/* NO MORE COPIES */
	if (stock <= 0)
	{
		return false;
	}
	else
	{
		stock -= 1;
	}
	return true;
}

bool Movie::returnMovie()
{
	/* ALL COPIES ACCOUNTED FOR */
	if (stock == intialStock)
	{
		return false;
	}
	else
	{
		stock += 1;
	}
	return true;
}


std::ostream & operator<<(std::ostream & outStream, Movie &outmMovie)
{
	outmMovie.print(outStream);

	return outStream;
}
