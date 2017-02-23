#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include <fstream>


class Command;
class Customer
{
	friend std::ostream& operator<<(std::ostream&, Customer&);
public:
	Customer();
	Customer(std::ifstream &inFile);
	Customer(int accNum, std::string fName, std::string lName);
	~Customer();

	std::string getName() const;
	void setName(std::string firName, std::string lasName);
	
	std::string getFirstName() const;
	void setFirst(std::string firName);
	
	std::string getLastName() const;
	void setLast(std::string lasName);

	int getAccountNumber() const;

	void addHistory(std::string newHistory);
	void showHistory();

private:
	int accountNumber;
	std::string firstName;
	std::string lastName;

	std::vector<std::string> history;

	void buildCustomer(std::ifstream &inFile);
};

#endif