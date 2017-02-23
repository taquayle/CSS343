#pragma once
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
	#include "History.h"
/********************/
class RentalStore
{
public:
	RentalStore();
	~RentalStore();

	bool buildStore(std::string movieData, std::string customerData);

	bool executeCommands(std::string commandData);

	bool sortMovieDatabase();

	void hash(std::string toHash);

private:
	
	std::vector<Customer*> customerDatabase;
	Movie *movieDatabase;
	std::vector<Movie*> comedyArray;
	std::vector<Movie*> dramaArray;
	std::vector<Movie*> classicArray;
	std::vector<Movie*> mainMovie;
	
	bool buildMovies(std::ifstream &inFile);
	bool buildCustomers(std::ifstream &inFile);
	bool buildCommands(std::ifstream &inFile);

	void returnCommand(std::ifstream &inFile);
	void borrowCommand(std::ifstream &inFile);
	
};