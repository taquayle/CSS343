#ifndef COMMAND_H
#define COMMAND_H
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Command.h													*/
/*	PARENT:		NONE														*/
/*	CHILDREN:	Borrow, History, Inventory, Return							*/
/****************************************************************************/
#include "Customer.h"
#include "Movie.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

class Command
{
protected:
	Command(int accNum, std::string medType, std::string movType);
public:
	Command();

	virtual ~Command();

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