/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Customer.cpp												*/
/*	PARENT:		NONE														*/
/*	CHILDREN:	NONE														*/
/****************************************************************************/
#include "Customer.h"
#include <string>


Customer::Customer()
{
accountNumber = -1;
firstName = "N/A";
lastName = "N/A";
}

Customer::Customer(std::ifstream &inFile)
{
	buildCustomer(inFile);
}

Customer::Customer(int accNum, std::string fName, std::string lName)
{
	accountNumber = accNum;
	firstName = fName;
	lastName = lName;
}


Customer::~Customer()
{
}

std::string Customer::getName() const
{
	return (firstName + " " + lastName);
}

void Customer::setName(std::string firName, std::string lasName)
{
	firstName = firName;
	lastName = lasName;
}

std::string Customer::getFirstName() const
{
	return firstName;
}

void Customer::setFirst(std::string firName)
{
	firstName = firName;
}

std::string Customer::getLastName() const
{
	return lastName;
}

void Customer::setLast(std::string lasName)
{
	lastName = lasName;
}

int Customer::getAccountNumber() const
{
	return accountNumber;
}

void Customer::addHistory(std::string newHistory)
{
	history.insert(history.begin(), newHistory);
	//history.push_back(newHistory);
}

void Customer::showHistory()
{
	int historySize = history.size();
	std::cout << "\n--- HISTORY ---";
	std::cout << std::endl << "Account Number: " << accountNumber <<
				"\nName " << firstName << " " << lastName << std::endl;
	if (historySize == 0)
	{
		std::cout << "ACCOUNT HAS NO HISTORY\n\n";
	}
	else
	{
		for (int i = 0; i < history.size(); i++)
		{
			std::cout << history[i] << std::endl;
		}
	}
}

void Customer::buildCustomer(std::ifstream &inFile)
{
	inFile >> accountNumber;
	inFile >> lastName;
	inFile >> firstName;
}
