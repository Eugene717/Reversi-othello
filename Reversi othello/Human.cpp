#include "Human.h"
#include <iostream>

using namespace std;

std::pair<int, int> Human::Move()
{
	int row, col;
	while (true)
	{
		cout << "Enter row(1-8): ";
		cin >> row;
		cout << "Enter col(1-8): ";
		cin >> col;

		--row;
		--col;
		
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error! You enter symbol\n";
		}
		if (row < -1 || row > 7 || col < -1 || col > 7)
			cout << "Wrong numbers!\t Try again!\n";
		else
			break;
	}	

	return pair<int, int>(row, col);
}
