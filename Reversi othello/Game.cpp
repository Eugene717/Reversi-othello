#include "Game.h"
#include "Human.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <random>
//#define DEBUG

const char BLACK = 'B', WHITE = 'W';

using namespace std;

class GameIMPL
{
public:
	GameIMPL(bool gameType);
	~GameIMPL();
	Human* m_humanOne;
	Human* m_humanTwo;
	short m_totalBlack = 0, m_totalWhite = 0;
	char m_board[8][8]{};
};

GameIMPL::GameIMPL(bool gameType) :m_board{}
{
	if (gameType)  //game of two humans on one PC
	{
		m_humanOne = new Human;
		m_humanTwo = new Human;
	}
	else
	{
		m_humanOne = new Human;
	}
}

GameIMPL::~GameIMPL()
{
	delete m_humanOne;
	if (m_humanTwo != nullptr)
		delete m_humanTwo;
}

Game::Game(bool gameType) :m_pImpl(new GameIMPL(gameType))
{
	m_pImpl->m_board[4][3] = BLACK;
	m_pImpl->m_board[3][4] = BLACK;
	m_pImpl->m_board[3][3] = WHITE;
	m_pImpl->m_board[4][4] = WHITE;
	m_pImpl->m_totalBlack = 2;
	m_pImpl->m_totalWhite = 2;
}

Game::~Game()
{
	delete m_pImpl;
}

void Game::Draw()
{
	system("cls");
	cout << "\n";
	cout << "\t\t\tBlack Chips: " << m_pImpl->m_totalBlack << "\t\t\t  White Chips: " << m_pImpl->m_totalWhite << "\n\n";
	cout << "\t\t\t\t    1   2   3   4   5   6   7   8\n";
	cout << "\t\t\t\t  #################################\n";
	for (size_t x = 0; x < 8; x++)
	{
		cout << "\t\t\t\t";
		cout << x + 1 << " | ";
		for (size_t y = 0; y < 8; y++)
		{
			if (m_pImpl->m_board[x][y] != BLACK && m_pImpl->m_board[x][y] != WHITE)
				cout << ' ';
			else
				cout << m_pImpl->m_board[x][y];
			cout << " | ";
		}
		if (x != 7)
			cout << "\n\t\t\t\t  |-------------------------------|" << endl;
		else
			cout << "\n\t\t\t\t  #################################" << endl << endl;
	}
}

inline bool Game::checkEmpty(const pair<int, int>& coord)
{
	if (m_pImpl->m_board[coord.first][coord.second] == '\0')
		return true;
	return false;
}

void Game::swapColor(const char& yourColor)
{
	if (yourColor == BLACK)
	{
		++m_pImpl->m_totalBlack;
		--m_pImpl->m_totalWhite;
	}
	else
	{
		--m_pImpl->m_totalBlack;
		++m_pImpl->m_totalWhite;
	}
}

int Game::checkHorizontal(const char& yourColor, const char& enemyColor, const pair<int, int>& coord, int* totalFlippedChips = nullptr)
{
	bool right = false, left = false;
	if (coord.second < 6)   //проверка справа
	{
		if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first][coord.second + 1] != yourColor && m_pImpl->m_board[coord.first][coord.second + 1] != '\0')
		{
			int hereFlipped = 0;
			for (size_t i = coord.second + 1; i < 8; i++)
			{
				if (m_pImpl->m_board[coord.first][i] == enemyColor)
				{
					canCheckYourColor = true;
					if (totalFlippedChips != nullptr)
					{
						++*totalFlippedChips;
						++hereFlipped;
					}
				}
				else if (canCheckYourColor)
				{
					if (m_pImpl->m_board[coord.first][i] == yourColor)
					{
						right = true;
						break;
					}
					else if (m_pImpl->m_board[coord.first][i] == '\0')  //если пусто
					{
						if (totalFlippedChips != nullptr)
							*totalFlippedChips -= hereFlipped;
						break;
					}
				}
			}
		}
	}
	if (coord.second > 1)   //проверка слева
	{
		if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first][coord.second - 1] != yourColor && m_pImpl->m_board[coord.first][coord.second - 1] != '\0')
		{
			int hereFlipped = 0;
			for (size_t i = coord.second - 1; i >= 0; i--)
			{
				if (m_pImpl->m_board[coord.first][i] == enemyColor)
				{
					canCheckYourColor = true;
					if (totalFlippedChips != nullptr)
					{
						++*totalFlippedChips;
						++hereFlipped;
					}
				}
				else if (canCheckYourColor)
				{
					if (m_pImpl->m_board[coord.first][i] == yourColor)
					{
						left = true;
						break;
					}
					else if (m_pImpl->m_board[coord.first][i] == '\0')  //если пусто
					{
						if (totalFlippedChips)
							*totalFlippedChips -= hereFlipped;
						break;
					}
				}
			}
		}
	}
	if (right && left)
		return 3;   //и слева и справа
	else if (!right && left)
		return 2;   //только слева
	else if (right && !left)
		return 1;   //только справа
	else
		return 0;
}

bool Game::flipHorizontal(const int& mode, const char& yourColor, const std::pair<int, int>& coord)
{
	switch (mode)
	{
	case 3:
		for (size_t i = coord.second - 1; i >= 0; i--)
		{
			if (m_pImpl->m_board[coord.first][i] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[coord.first][i] = yourColor;
				swapColor(yourColor);
			}
		}
		for (size_t i = coord.second + 1; i < 8; i++)
		{
			if (m_pImpl->m_board[coord.first][i] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[coord.first][i] = yourColor;
				swapColor(yourColor);
			}
		}
	case 2:
		for (size_t i = coord.second - 1; i >= 0; i--)
		{
			if (m_pImpl->m_board[coord.first][i] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[coord.first][i] = yourColor;
				swapColor(yourColor);
			}
		}
	case 1:
		for (size_t i = coord.second + 1; i < 8; i++)
		{
			if (m_pImpl->m_board[coord.first][i] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[coord.first][i] = yourColor;
				swapColor(yourColor);
			}
		}
	case 0:
		return false;
	}
}

int Game::checkVertical(const char& yourColor, const char& enemyColor, const std::pair<int, int>& coord, int* totalFlippedChips = nullptr)
{
	bool up = false, down = false;

		if (coord.first < 6)   //проверка снизу
		{
			if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first + 1][coord.second] != yourColor && m_pImpl->m_board[coord.first + 1][coord.second] != '\0')
			{
				int hereFlipped = 0;
				for (size_t i = coord.first + 1; i < 8; i++)
				{
					if (m_pImpl->m_board[i][coord.second] == enemyColor)
					{
						canCheckYourColor = true;
						if (totalFlippedChips != nullptr)
						{
							++*totalFlippedChips;
							++hereFlipped;
						}
					}
					else if (canCheckYourColor)
					{
						if (m_pImpl->m_board[i][coord.second] == yourColor)
						{
							down = true;
							break;
						}
						else if (m_pImpl->m_board[i][coord.second] == '\0')  //если пусто
						{
							if (totalFlippedChips != nullptr)
								*totalFlippedChips -= hereFlipped;
							break;
						}
					}
				}
			}
		}
		if (coord.first > 1)   //проверка сверху
		{
			if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first - 1][coord.second] != yourColor && m_pImpl->m_board[coord.first - 1][coord.second] != '\0')
			{
				int hereFlipped = 0;
				for (size_t i = coord.first - 1; i >= 0; i--)
				{
					if (m_pImpl->m_board[i][coord.second] == enemyColor)
					{
						canCheckYourColor = true;
						if (totalFlippedChips != nullptr)
						{
							++*totalFlippedChips;
							++hereFlipped;
						}
					}
					else if (canCheckYourColor)
					{
						if (m_pImpl->m_board[i][coord.second] == yourColor)
						{
							up = true;
							break;
						}
						else if (m_pImpl->m_board[i][coord.second] == '\0')  //если пусто
						{
							if (totalFlippedChips != nullptr)
								*totalFlippedChips -= hereFlipped;
							break;
						}
					}
				}
			}
		}

	if (up && down)
		return 3;   //и сверху и снизу
	else if (!up && down)
		return 2;   //только снизу
	else if (up && !down)
		return 1;   //только сверху
	else
		return 0;
}

bool Game::flipVertical(const int& mode, const char& yourColor, const std::pair<int, int>& coord)
{
	switch (mode)
	{
	case 3:
		for (size_t i = coord.first - 1; i >= 0; i--)
		{
			if (m_pImpl->m_board[i][coord.second] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[i][coord.second] = yourColor;
				swapColor(yourColor);
			}
		}
		for (size_t i = coord.first + 1; i < 8; i++)
		{
			if (m_pImpl->m_board[i][coord.second] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[i][coord.second] = yourColor;
				swapColor(yourColor);
			}
		}
	case 2:
		for (size_t i = coord.first + 1; i < 8; i++)
		{
			if (m_pImpl->m_board[i][coord.second] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[i][coord.second] = yourColor;
				swapColor(yourColor);
			}
		}
	case 1:
		for (size_t i = coord.first - 1; i >= 0; i--)
		{
			if (m_pImpl->m_board[i][coord.second] == yourColor)
			{
				return true;
			}
			else
			{
				m_pImpl->m_board[i][coord.second] = yourColor;
				swapColor(yourColor);
			}
		}
	case 0:
		return false;
	}
}

int Game::checkDiagonal(const char& yourColor, const char& enemyColor, const std::pair<int, int>& coord, int* totalFlippedChips = nullptr)
{
	bool rightUp = false, rightDown = false, leftDown = false, leftUp = false;

	if (coord.first > 1 && coord.second < 6)  //right-up
	{
		if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first - 1][coord.second + 1] != yourColor && m_pImpl->m_board[coord.first - 1][coord.second + 1] != '\0')
		{
			int hereFlipped = 0;
			for (size_t x = coord.first - 1, y = coord.second + 1; x >= 0 && y < 8; x--, y++)
			{
				if (m_pImpl->m_board[x][y] == enemyColor)
				{
					canCheckYourColor = true;
					if (totalFlippedChips != nullptr)
					{
						++*totalFlippedChips;
						++hereFlipped;
					}
				}
				else if (canCheckYourColor)
				{
					if (m_pImpl->m_board[x][y] == yourColor)
					{
						rightUp = true;
						break;
					}
					else if (m_pImpl->m_board[x][y] == '\0')  //если пусто
					{
						if (totalFlippedChips != nullptr)
							*totalFlippedChips -= hereFlipped;
						break;
					}
				}
			}
		}
	}
	if (coord.first < 6 && coord.second < 6)   //right-down
	{
		if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first + 1][coord.second + 1] != yourColor && m_pImpl->m_board[coord.first + 1][coord.second + 1] != '\0')
		{
			int hereFlipped = 0;
			for (size_t x = coord.first + 1, y = coord.second + 1; x < 8 && y < 8; x++, y++)
			{
				if (m_pImpl->m_board[x][y] == enemyColor)
				{
					canCheckYourColor = true;
					if (totalFlippedChips != nullptr)
					{
						++*totalFlippedChips;
						++hereFlipped;
					}
				}
				else if (canCheckYourColor)
				{
					if (m_pImpl->m_board[x][y] == yourColor)
					{
						rightDown = true;
						break;
					}
					else if (m_pImpl->m_board[x][y] == '\0')  //если пусто
					{
						if (totalFlippedChips != nullptr)
							*totalFlippedChips -= hereFlipped;
						break;
					}
				}
			}
		}
	}
	if (coord.first < 6 && coord.second > 1)   //left-down
	{
		if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first + 1][coord.second - 1] != yourColor && m_pImpl->m_board[coord.first + 1][coord.second - 1] != '\0')
		{
			int hereFlipped = 0;
			for (int x = coord.first + 1, y = coord.second - 1; x < 8 && y >= 0; x++, y--)
			{
				if (m_pImpl->m_board[x][y] == enemyColor)
				{
					canCheckYourColor = true;
					if (totalFlippedChips != nullptr)
					{
						++*totalFlippedChips;
						++hereFlipped;
					}
				}
				else if (canCheckYourColor)
				{
					if (m_pImpl->m_board[x][y] == yourColor)
					{
						leftDown = true;
						break;
					}
					else if (m_pImpl->m_board[x][y] == '\0')  //если пусто
					{
						if (totalFlippedChips != nullptr)
							*totalFlippedChips -= hereFlipped;
						break;
					}
				}
			}
		}
	}
	if (coord.first > 1 && coord.second > 1)   //left-up
	{
		if (bool canCheckYourColor = false; m_pImpl->m_board[coord.first - 1][coord.second - 1] != yourColor && m_pImpl->m_board[coord.first - 1][coord.second - 1] != '\0')
		{
			int hereFlipped = 0;
			for (size_t x = coord.first - 1, y = coord.second - 1; x >= 0 && y >= 0; x--, y--)
			{
				if (m_pImpl->m_board[x][y] == enemyColor)
				{
					canCheckYourColor = true;
					if (totalFlippedChips != nullptr)
					{
						++*totalFlippedChips;
						++hereFlipped;
					}
				}
				else if (canCheckYourColor)
				{
					if (m_pImpl->m_board[x][y] == yourColor)
					{
						leftUp = true;
						break;
					}
					else if (m_pImpl->m_board[x][y] == '\0')  //если пусто
					{
						if (totalFlippedChips != nullptr)
							*totalFlippedChips -= hereFlipped;
						break;
					}
				}
			}
		}
	}

	int res = 0;
	if (rightUp)
		res += 1000;
	if (rightDown)
		res += 100;
	if (leftDown)
		res += 10;
	if (leftUp)
		res += 1;

	return res;   //4-х значное число  //1001, 0110
}

bool Game::flipDiagonal(const int& mode, const char& yourColor, const std::pair<int, int>& coord)
{
	bool res = false;
	if (mode / 1000 > 0)   //right-up
	{
		for (size_t i = coord.first - 1, j = coord.second + 1; i >= 0 && j < 8; i--, j++)
		{
			if (m_pImpl->m_board[i][j] == yourColor)
			{
				res = true;
				break;
			}
			else
			{
				m_pImpl->m_board[i][j] = yourColor;
				swapColor(yourColor);
			}
		}
	}
	if (mode % 1000 / 100 > 0)   //right-down
	{
		for (size_t i = coord.first + 1, j = coord.second + 1; i < 8 && j < 8; i++, j++)
		{
			if (m_pImpl->m_board[i][j] == yourColor)
			{
				res = true;
				break;
			}
			else
			{
				m_pImpl->m_board[i][j] = yourColor;
				swapColor(yourColor);
			}
		}
	}
	if (mode % 1000 % 100 / 10 > 0)   //left-down
	{
		for (size_t i = coord.first + 1, j = coord.second - 1; i < 8 && j >= 0; i++, j--)
		{
			if (m_pImpl->m_board[i][j] == yourColor)
			{
				res = true;
				break;
			}
			else
			{
				m_pImpl->m_board[i][j] = yourColor;
				swapColor(yourColor);
			}
		}
	}
	if (mode % 1000 % 100 % 10 > 0)   //left-up
	{
		for (size_t i = coord.first - 1, j = coord.second - 1; i >= 0 && j >= 0; i--, j--)
		{
			if (m_pImpl->m_board[i][j] == yourColor)
			{
				res = true;
				break;
			}
			else
			{
				m_pImpl->m_board[i][j] = yourColor;
				swapColor(yourColor);
			}
		}
	}
	return res;
}

bool Game::checkAvailableTurn(const char& yourColor, const char& enemyColor)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (!checkEmpty(pair<int, int>(i, j)))
				continue;

			if (checkHorizontal(yourColor, enemyColor, pair<int, int>(i, j)) > 0)
				return true;

			if (checkVertical(yourColor, enemyColor, pair<int, int>(i, j)) > 0)
				return true;

			if (checkDiagonal(yourColor, enemyColor, pair<int, int>(i, j)) > 0)
				return true;
		}
	}
	return false;
}

bool Game::CheckGameOver()
{
	for (size_t x = 0; x < 8; x++)
	{
		for (size_t y = 0; y < 8; y++)
		{
			if (m_pImpl->m_board[x][y] != BLACK && m_pImpl->m_board[x][y] != WHITE)
			{
				return false;
			}
		}
	}
	return true;
}

void Game::AnnounceWinner()
{
	if (m_pImpl->m_totalBlack > m_pImpl->m_totalWhite)
	{
		cout << "Black = " << m_pImpl->m_totalBlack << "White = " << m_pImpl->m_totalWhite << endl;
		cout << "BLACK PLAYER WIN!\n";
	}
	else if (m_pImpl->m_totalWhite > m_pImpl->m_totalBlack)
	{
		cout << "Black = " << m_pImpl->m_totalBlack << "White = " << m_pImpl->m_totalWhite << endl;
		cout << "WHITE PLAYER WIN!\n";
	}
	else
	{
		cout << "Black = 32 && White = 32\n";
		cout << "DRAW!\n";
	}
}

void Game::FindBestTurn(pair<int, int>& coordBestTurn)
{
	int bestTurn = 0;
	list<pair<int, int>> coords;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int thisTurn = 0;
			if (checkEmpty(pair<int, int>(i, j)))
			{
				checkHorizontal(WHITE, BLACK, pair<int, int>(i, j), &thisTurn);
				checkVertical(WHITE, BLACK, pair<int, int>(i, j), &thisTurn);
				checkDiagonal(WHITE, BLACK, pair<int, int>(i, j), &thisTurn);
				if (thisTurn > bestTurn)
				{
					bestTurn = thisTurn;
					coords.clear();
					coords.push_back(pair<int, int>(i, j));
				}
				else if (thisTurn == bestTurn && coords.size() > 0)
				{
					coords.push_back(pair<int, int>(i, j));
				}
			}
		}
	}
	random_device rd;
	int random = rd() % coords.size();

	auto bestCoord = coords.begin();
	advance(bestCoord, random);
	coordBestTurn = *bestCoord;
}

void Game::SinglePlayer()
{
#ifdef DEBUG
	pair<int, int> coord;
	do
	{
		while (true)
		{
			Draw();
			coord = m_pImpl->m_humanOne->Move();
			bool rightTurnHoriz;
			bool rightTurnVert;
			bool rightTurnDiag;
			if (bool rightTurnHoriz, rightTurnVert, rightTurnDiag; checkEmpty(coord))
			{
				m_pImpl->m_board[coord.first][coord.second] = BLACK;
				rightTurnHoriz = flipHorizontal(checkHorizontal(BLACK, WHITE, coord), BLACK, coord);
				rightTurnVert = flipVertical(checkVertical(BLACK, WHITE, coord), BLACK, coord);
				rightTurnDiag = flipDiagonal(checkDiagonal(BLACK, WHITE, coord), BLACK, coord);
				if (rightTurnHoriz || rightTurnVert || rightTurnDiag)
					break;
				else
					m_pImpl->m_board[coord.first][coord.second] = '\0';
			}
		}




		Draw();
		coord = m_pImpl->m_humanTwo->Move();
		m_pImpl->m_board[coord.first][coord.second] = WHITE;


	} while (!CheckGameOver());
	AnnounceWinner();
#else
	pair<int, int> coord;
	do
	{
		bool noMovesOne = false, noMovesTwo = false;
		while (true)
		{
			Draw();
			if (!checkAvailableTurn(BLACK, WHITE))
			{
				cout << "NO MOVE AVAILABLE!\n";
				system("pause");
				noMovesOne = true;
				break;
			}
			coord = m_pImpl->m_humanOne->Move();
			bool rightTurnHoriz;
			bool rightTurnVert;
			bool rightTurnDiag;
			if (bool rightTurnHoriz, rightTurnVert, rightTurnDiag; checkEmpty(coord))
			{
				m_pImpl->m_board[coord.first][coord.second] = BLACK;
				rightTurnHoriz = flipHorizontal(checkHorizontal(BLACK, WHITE, coord), BLACK, coord);
				rightTurnVert = flipVertical(checkVertical(BLACK, WHITE, coord), BLACK, coord);
				rightTurnDiag = flipDiagonal(checkDiagonal(BLACK, WHITE, coord), BLACK, coord);
				if (rightTurnHoriz || rightTurnVert || rightTurnDiag)
				{
					++m_pImpl->m_totalBlack;
					break;
				}
				else
					m_pImpl->m_board[coord.first][coord.second] = '\0';
			}
			cout << "The chip cannot be here, choose another place!\n";
			system("pause");
		}
		if (CheckGameOver())
		{
			Draw();
			break;
		}
		while (true)
		{
			Draw();
			if (!checkAvailableTurn(WHITE, BLACK))
			{
				cout << "NO MOVE AVAILABLE!\n";
				system("pause");
				noMovesTwo = true;
				break;
			}
			coord = m_pImpl->m_humanOne->Move();
			bool rightTurnHoriz;
			bool rightTurnVert;
			bool rightTurnDiag;
			if (bool rightTurnHoriz, rightTurnVert, rightTurnDiag; checkEmpty(coord))
			{
				m_pImpl->m_board[coord.first][coord.second] = WHITE;
				rightTurnHoriz = flipHorizontal(checkHorizontal(WHITE, BLACK, coord), WHITE, coord);
				rightTurnVert = flipVertical(checkVertical(WHITE, BLACK, coord), WHITE, coord);
				rightTurnDiag = flipDiagonal(checkDiagonal(WHITE, BLACK, coord), WHITE, coord);
				if (rightTurnHoriz || rightTurnVert || rightTurnDiag)
				{
					++m_pImpl->m_totalWhite;
					break;
				}
				else
					m_pImpl->m_board[coord.first][coord.second] = '\0';
			}
			cout << "The chip cannot be here, choose another place!\n";
			system("pause");
		}
		Draw();
		if (noMovesOne && noMovesTwo)
		{
			cout << "Two player cannot Move!\n\t\t\tGame Over!\n";
			system("pause");
			break;
		}
	} while (!CheckGameOver());
	AnnounceWinner();
#endif  //DEBUG
}

void Game::WithAI()
{
	do
	{
		bool noMovesOne = false, noMovesTwo = false;
		while (true)   //игрок
		{
			Draw();
			if (!checkAvailableTurn(BLACK, WHITE))
			{
				cout << "NO MOVE AVAILABLE!\n";
				system("pause");
				noMovesOne = true;
				break;
			}
			pair<int, int> coord;
			coord = m_pImpl->m_humanOne->Move();
			bool rightTurnHoriz;
			bool rightTurnVert;
			bool rightTurnDiag;
			if (bool rightTurnHoriz, rightTurnVert, rightTurnDiag; checkEmpty(coord))
			{
				m_pImpl->m_board[coord.first][coord.second] = BLACK;
				rightTurnHoriz = flipHorizontal(checkHorizontal(BLACK, WHITE, coord), BLACK, coord);
				rightTurnVert = flipVertical(checkVertical(BLACK, WHITE, coord), BLACK, coord);
				rightTurnDiag = flipDiagonal(checkDiagonal(BLACK, WHITE, coord), BLACK, coord);
				if (rightTurnHoriz || rightTurnVert || rightTurnDiag)
				{
					++m_pImpl->m_totalBlack;
					break;
				}
				else
					m_pImpl->m_board[coord.first][coord.second] = '\0';
			}
			cout << "The chip cannot be here, choose another place!\n";
			system("pause");
		}
		if (CheckGameOver())
		{
			Draw();
			break;
		}		
		while (true)   //ИИ
		{
			Draw();
			if (!checkAvailableTurn(WHITE, BLACK))
			{
				cout << "NO MOVE AVAILABLE!\n";
				system("pause");
				noMovesTwo = true;
				break;
			}
			pair<int, int> coordBestTurn(0, 0);
			FindBestTurn(coordBestTurn);
			m_pImpl->m_board[coordBestTurn.first][coordBestTurn.second] = WHITE;
			flipHorizontal(checkHorizontal(WHITE, BLACK, coordBestTurn), WHITE, coordBestTurn);
			flipVertical(checkVertical(WHITE, BLACK, coordBestTurn), WHITE, coordBestTurn);
			flipDiagonal(checkDiagonal(WHITE, BLACK, coordBestTurn), WHITE, coordBestTurn);
			++m_pImpl->m_totalWhite;
			break;
		}
		Draw();
		if (noMovesOne && noMovesTwo)
		{
			cout << "Two player cannot Move!\n\t\t\tGame Over!\n";
			system("pause");
			break;
		}
	} while (!CheckGameOver());
}

void Play(const bool& mode)
{
	Game game(mode);
	if (mode)
		game.SinglePlayer();
	else
		game.WithAI();
}
