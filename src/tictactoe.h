#ifndef INCLUDED_TICTACTOE_H
#define INCLUDED_TICTACTOE_H

#include <vector>
#include <ctime>

namespace tictactoe
{

class TicTacToe
{

private:
	typedef std::vector<std::vector<char>> Board;

	typedef std::pair<int, int> Cell;

	Board d_board;

public:
	TicTacToe();

	void startGame();

private:
	int miniMax(Board board, int flag);

	int evaluate(const Board &board) const;

	Cell nextbestMove();

	void printBoard() const;

	int makeMove(const Cell &bestMove, int flag);
};

}; // namespace tictactoe
#endif