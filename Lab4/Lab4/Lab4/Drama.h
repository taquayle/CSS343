#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Drama.h														*/
/*	PARENT:		Movie														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Movie.h"
class Drama: public Movie
{
	//friend std::ostream& operator<<(std::ostream&, Drama&);
public:
	Drama();
	Drama(std::ifstream &inFile);
	Drama(int _year, int _stock, std::string dirFirst, std::string dirLast, std::string _title);
	~Drama();

	// Inherited via Movie
	virtual void print(std::ostream &indirect);
	virtual void buildMovie(std::ifstream &inFile);
	virtual int getReleaseMonth() const;
	virtual void setReleaseMonth(int relMonth);
	virtual bool checkCast(std::string actorCheck);

	bool operator==(const Drama&) const;
	bool operator!=(const Drama&) const;

	bool operator<(const Drama&) const;
	bool operator>(const Drama&) const;
};

