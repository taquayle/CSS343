#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Classic.H													*/
/*	PARENT:		Movie														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Movie.h"
class Classic: public Movie
{
public:
	Classic();
	Classic(std::ifstream &inFile);
	Classic(int relYear, int relMonth, int _stock, std::string _actor, std::string dirFirst, std::string dirLast, std::string _title);
	~Classic();

	// Inherited via Movie
	virtual void print(std::ostream & indirect);
	virtual void buildMovie(std::ifstream &inFile);

	virtual int getReleaseMonth() const;
	virtual void setReleaseMonth(int relMonth);

	void setActor(std::string _actor);
	std::string getMainAct() const;
	void getActors(std::ostream &actorOut) const;
	virtual bool checkCast(std::string actorCheck);


	void sameMovie(int _stock, std::string _actor);

	bool operator==(const Classic&) const;
	bool operator!=(const Classic&) const;

	bool operator<(const Classic&) const;
	bool operator>(const Classic&) const;
private:
	int releaseMonth;
	std::vector<std::string> actors;

	void addActor(std::string _actor);
	void addStock(int _stock);
	
};
