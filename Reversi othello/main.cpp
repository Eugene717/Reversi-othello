#include "pch.h"

using namespace std;

int main()
{
	while (true)
	{
		system("cls");
		cout << "Good morning!\n";
		cout << "Choice game mode\n1 - game of two humans on one PC\n2 - game with AI\n3 - exit\n";
		switch (_getch())
		{
		case '1':
			system("cls");
			Play(true);
			break;
		case '2':
			system("cls");
			Play(false);
			break;
		case '3':
			cout << "BB\n";
			return 0;
		default:
			system("cls");
			cout << "wrong key!\n";
			break;
		}
	}
}
