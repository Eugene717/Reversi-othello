#pragma once
#include <utility>

class GameIMPL;

class Game
{
	GameIMPL* m_pImpl;
	bool CheckGameOver();
	void AnnounceWinner();
	inline bool checkEmpty(const std::pair<int,int>& coord);
	void swapColor(const char& yourColor);
	int checkHorizontal(const char& yourColor, const char& enemyColor, const std::pair<int, int>& coord, int* totalFlippedChips);
	int checkVertical(const char& yourColor, const char& enemyColor, const std::pair<int, int>& coord, int* totalFlippedChips);
	int checkDiagonal(const char& yourColor, const char& enemyColor, const std::pair<int, int>& coord, int* totalFlippedChips);
	bool flipHorizontal(const int& mode, const char& yourColor, const std::pair<int, int>& coord);
	bool flipVertical(const int& mode, const char& yourColor, const std::pair<int, int>& coord);
	bool flipDiagonal(const int& mode, const char& yourColor, const std::pair<int, int>& coord);
	bool checkAvailableTurn(const char& yourColor, const char& enemyColor);
	void FindBestTurn(std::pair<int, int>& coordBestTurn);
public:
	Game(bool gameType);
	~Game();
	void Draw();
	void SinglePlayer();
	void WithAI();
};

void Play(const bool& mode);
