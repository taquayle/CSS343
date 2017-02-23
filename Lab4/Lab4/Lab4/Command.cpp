/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Command.cpp													*/
/*	PARENT:		NONE														*/
/*	CHILDREN:	History, Invetory, Borrow, Return							*/
/****************************************************************************/
#include "Command.h"

Command::Command()
{
accountNumber = -1;
mediaType = "N/A";
movieType = "N/A";
}

Command::Command(int accNum, std::string medType, std::string movType)
{
	accountNumber = accNum;
	mediaType = medType;
	movieType = movType;
}


Command::~Command()
{
}

int Command::getAccountNumber() const
{
	return accountNumber;
}

void Command::setAccountNumber(int accNum)
{
	accountNumber = accNum;
}

std::string Command::getMediaType() const
{
	return mediaType;
}

void Command::setMediaType(std::string medType)
{
	mediaType = medType;
}

std::string Command::getMovieType() const
{
	return movieType;
}

void Command::setMovieType(std::string movType)
{
	movieType = movType;
}
