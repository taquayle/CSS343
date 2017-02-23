#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Comedy.h													*/
/*	PARENT:		Movie														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Movie.h"
class Comedy: public Movie
{
	friend std::ostream& operator<<(std::ostream&, Comedy&);
public:
	Comedy();
	Comedy(std::ifstream &inFile);
	Comedy(int _year, int _stock, std::string dirFirst, std::string dirLast, std::string _title);
	~Comedy();
	
	// Inherited via Movie
	virtual void print(std::ostream & indirect);
	virtual void buildMovie(std::ifstream &inFile);
	virtual int getReleaseMonth() const;
	virtual void setReleaseMonth(int relMonth);
	virtual bool checkCast(std::string actorCheck);

	bool operator==(const Comedy&) const;
	bool operator!=(const Comedy&) const;

	bool operator<(const Comedy&) const;
	bool operator>(const Comedy&) const;
};

