#pragma once
#include "Movie.h"
class Drama: public Movie
{
	//friend std::ostream& operator<<(std::ostream&, Drama&);
public:
	Drama();
	Drama(std::ifstream &inFile);
	Drama(int _year, int _stock, std::string dirFirst, std::string dirLast, std::string _title);
	~Drama();

	int getYear() const;
	void setYear(int _year);

	// Inherited via Movie
	virtual void print(std::ostream &indirect);
	virtual void getMovie(std::ifstream &inFile);
	// Inherited via Movie
	virtual int getReleaseMonth() const;
	virtual void setReleaseMonth(int relMonth);
	virtual bool checkCast(std::string actorCheck);

	bool operator==(const Drama&) const;
	bool operator!=(const Drama&) const;

	bool operator<(const Drama&) const;
	bool operator>(const Drama&) const;
private:
	int year;
};

