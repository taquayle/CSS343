#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

class Movie
{
	friend std::ostream& operator<<(std::ostream&, Movie&);
protected:
	Movie(int year, int _stock, std::string dirFirst, std::string dirLast, std::string _title);
public:
	Movie();

	virtual ~Movie();

	/*************************************************************************/
	std::string getTitle() const;
	void setTitle(std::string _title);
	
	std::string getDirector() const;
	void setDirector(std::string dirFirst, std::string dirLast);
	
	int getStock() const;
	void setStock(int _stock);

	int getReleaseYear() const;
	void setReleaseYear(int _year);
	/*************************************************************************/

	virtual int getReleaseMonth() const = 0;
	virtual void setReleaseMonth(int relMonth) = 0;

	virtual bool checkCast(std::string actorCheck) = 0;

	virtual bool borrowMovie();
	virtual bool returnMovie();

	virtual void getMovie(std::ifstream &inFile) = 0;
	virtual void print(std::ostream &indirect) = 0;

	bool operator==(const Movie&) const;
	bool operator!=(const Movie&) const;

	bool operator<(const Movie&) const;
	bool operator>(const Movie&) const;

protected:
	int stock;
	int releaseYear;
	std::string directFirst;
	std::string directLast;
	std::string title;
};

#endif