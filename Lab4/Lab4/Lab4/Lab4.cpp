/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Lab4.cpp													*/
/*	PARENT:		NONE														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "RentalStore.h"
#include <iomanip>

using namespace std;

int main()
{
	
	std::cout << "/******************************************************************************/\n";
	std::cout << "/*	PROJECT: LAB4\n";
	std::cout << "/*	TEAM: Assignment4 19\n";
	std::cout << "/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas\n";
	std::cout << "/******************************************************************************/\n";
	RentalStore test;
	if (test.buildDatabases("data4movies.txt", "data4customers.txt", "data4commands.txt"))
	{
		test.executeCommands();
	}



	system("pause");
	return 0;
}