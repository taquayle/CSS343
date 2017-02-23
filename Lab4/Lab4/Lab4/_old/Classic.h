#pragma once
#include "Movie.h"
class Classic: public Movie
{
public:
	Classic();
	Classic(std::ifstream &inFile);
	Classic(int relYear, int relMonth, int _stock, std::string actFirst, std::string actLast, std::string dirFirst, std::string dirLast, std::string _title);
	~Classic();

	// Inherited via Movie
	virtual void print(std::ostream & indirect);
	virtual void getMovie(std::ifstream &inFile);

	virtual int getReleaseMonth() const;
	virtual void setReleaseMonth(int relMonth);

	void setActor(std::string actFirst, std::string actLast);
	void getActors(std::ostream &actorOut) const;
	virtual bool checkCast(std::string actorCheck);


	void sameMovie(int _stock, std::string actFirst, std::string actLast);

	bool operator==(const Classic&) const;
	bool operator!=(const Classic&) const;

	bool operator<(const Classic&) const;
	bool operator>(const Classic&) const;
private:
	int releaseMonth;
	std::vector<std::string> actors;

	void addActor(std::string actFirst, std::string actLast);
	void addStock(int _stock);
	
};
