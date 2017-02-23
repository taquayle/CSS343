#ifndef COMMAND_H
#define COMMAND_H

#include "Customer.h"
#include "Movie.h"
#include <cstdlib>
#include <fstream>

class Command
{
protected:
	Command(int accNum, std::string medType, std::string movType);
public:
	Command();

	~Command();

	int getAccountNumber() const;
	void setAccountNumber(int accNum);

	std::string getMediaType() const;
	void setMediaType(std::string medType);

	std::string getMovieType() const;
	void setMovieType(std::string movType);

	virtual bool executeCommand(std::vector<Customer*> &, std::vector<Movie*> &)  = 0;
private:
	int accountNumber;
	std::string mediaType;
	std::string movieType;
};

#endif