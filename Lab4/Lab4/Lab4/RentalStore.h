#pragma once
/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		RentalStore.h												*/
/*	PARENT:		NONE														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
/********************/
#include "Customer.h"
#include "Movie.h"
	#include "Drama.h"
	#include "Comedy.h"
	#include "Classic.h"
#include "Command.h"
	#include "Inventory.h"
	#include "Return.h"
		#include "ReturnClassic.h"
		#include "ReturnDrama.h"
		#include "ReturnComedy.h"
	#include "Borrow.h"
		#include "BorrowClassic.h"
		#include "BorrowComedy.h"
		#include "BorrowDrama.h"
	#include "History.h"
/********************/
class RentalStore
{
public:
	RentalStore();
	~RentalStore();

	bool buildDatabases(std::string movieFileName, std::string customerFileName, std::string commandFileName);

	bool executeCommands();

	bool sortMovieDatabase();

	void hash(std::string toHash);

private:
	
	std::vector<Customer*> customerDB;
	std::vector<Command*> commandDB;
	std::vector<Movie*> movieDB;
		std::vector<Movie*> comedyArray;
		std::vector<Movie*> dramaArray;
		std::vector<Movie*> classicArray;

	
	bool buildMovies(std::ifstream &inFile);
	bool buildCustomers(std::ifstream &inFile);
	bool buildCommands(std::ifstream &inFile);

	void returnCommand(std::ifstream &inFile);
	void borrowCommand(std::ifstream &inFile);
};