#include "RentalStore.h"
#include <iomanip>

using namespace std;

int main()
{
	RentalStore test;
	test.buildStore("data4movies.txt", "data4customers.txt");
	test.executeCommands("data4commands.txt");


	system("pause");
	return 0;
}