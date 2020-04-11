#include <algorithm>
#include <iostream>
#include <tictactoe.h>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;

namespace tictactoe
{

TicTacToe::TicTacToe() : d_board(3, {' ', ' ', ' '})
{
}

int TicTacToe::miniMax(Board d_board, int flag)
{
	const int rc = evaluate(d_board);

	if (-1 <= rc && 1 >= rc)
	{
		return rc;
	}

	if (0 == flag)
	{
		int ret = 10;
		for (size_t i = 0; i < d_board.size(); ++i)
		{
			for (size_t j = 0; j < d_board[i].size(); ++j)
			{
				if (' ' == d_board[i][j])
				{
					d_board[i][j] = 'O';
					ret = min(ret, miniMax(d_board, 1));
					d_board[i][j] = ' ';
				}
			}
		}
		return ret;
	}
	else
	{
		int ret = -10;
		for (size_t i = 0; i < d_board.size(); ++i)
		{
			for (size_t j = 0; j < d_board[i].size(); ++j)
			{
				if (' ' == d_board[i][j])
				{
					d_board[i][j] = 'x';
					ret = max(ret, miniMax(d_board, 0));
					d_board[i][j] = ' ';
				}
			}
		}
		return ret;
	}
	return 0;
}

int TicTacToe::evaluate(const Board &d_board) const
{
	//check rows
	if ((d_board[0][0] == 'x' && d_board[0][1] == 'x' && d_board[0][2] == 'x') ||
		(d_board[1][0] == 'x' && d_board[1][1] == 'x' && d_board[1][2] == 'x') ||
		(d_board[2][0] == 'x' && d_board[2][1] == 'x' && d_board[2][2] == 'x'))
		return 1;
	if ((d_board[0][0] == 'O' && d_board[0][1] == 'O' && d_board[0][2] == 'O') ||
		(d_board[1][0] == 'O' && d_board[1][1] == 'O' && d_board[1][2] == 'O') ||
		(d_board[2][0] == 'O' && d_board[2][1] == 'O' && d_board[2][2] == 'O'))
		return -1;

	//check columns
	if ((d_board[0][0] == 'x' && d_board[1][0] == 'x' && d_board[2][0] == 'x') ||
		(d_board[0][1] == 'x' && d_board[1][1] == 'x' && d_board[2][1] == 'x') ||
		(d_board[0][2] == 'x' && d_board[1][2] == 'x' && d_board[2][2] == 'x'))
		return 1;
	if ((d_board[0][0] == 'O' && d_board[1][0] == 'O' && d_board[2][0] == 'O') ||
		(d_board[0][1] == 'O' && d_board[1][1] == 'O' && d_board[2][1] == 'O') ||
		(d_board[0][2] == 'O' && d_board[1][2] == 'O' && d_board[2][2] == 'O'))
		return -1;

	//check diagonals
	if ((d_board[0][0] == 'x' && d_board[1][1] == 'x' && d_board[2][2] == 'x') ||
		(d_board[0][2] == 'x' && d_board[1][1] == 'x' && d_board[2][0] == 'x'))
		return 1;
	if ((d_board[0][0] == 'O' && d_board[1][1] == 'O' && d_board[2][2] == 'O') ||
		(d_board[0][2] == 'O' && d_board[1][1] == 'O' && d_board[2][0] == 'O'))
		return -1;

	//If d_board is full, return 0 else return -2
	for (size_t i = 0; i < d_board.size(); ++i)
	{
		for (size_t j = 0; j < d_board[i].size(); ++j)
		{
			if (' ' == d_board[i][j])
				return -2;
		}
	}
	return 0;
}

TicTacToe::Cell TicTacToe::nextbestMove()
{
	int ret = -10, temp, iBest = -1, jBest = -1;
	for (size_t i = 0; i < d_board.size(); ++i)
	{
		for (size_t j = 0; j < d_board[i].size(); ++j)
		{
			if (' ' == d_board[i][j])
			{
				d_board[i][j] = 'x';
				temp = miniMax(d_board, 0);
				if (temp > ret)
				{
					iBest = i;
					jBest = j;
					ret = temp;
				}
				d_board[i][j] = ' ';
			}
		}
	}
	return Cell(iBest, jBest);
}

void TicTacToe::printBoard() const
{
	for (size_t i = 0; i < 3; ++i)
	{
		if (0 == i)
		{
			cout << " ";
			for (size_t j = 0; j < 3; ++j)
				cout << "___"
					 << " ";
			cout << endl;
		}
		else
		{
			cout << "|";
			for (size_t j = 0; j < 3; ++j)
				cout << "___"
					 << "|";
			cout << endl;
		}
		cout << "|";
		for (size_t j = 0; j < 3; ++j)
			cout << " " << d_board[i][j] << " "
				 << "|";
		cout << endl;
	}
	cout << "|";
	for (size_t i = 0; i < 3; ++i)
		cout << "___"
			 << "|";
	cout << endl;
	return;
}

int TicTacToe::makeMove(const Cell &bestMove, int flag)
{
	if (d_board[bestMove.first][bestMove.second] != ' ')
	{
		return -3;
	}

	if (0 == flag)
	{
		d_board[bestMove.first][bestMove.second] = 'O';
	}
	else
	{
		d_board[bestMove.first][bestMove.second] = 'x';
	}
	return evaluate(d_board);
}

void TicTacToe::startGame()
{
	srand(time(nullptr));
	int x, y, i = 0;
	char inp;
	cout << "Welcome Opponent! You are 'O' and I am 'x'. Sorry, no options here." << endl
		 << "But I will let you play first if you want. " << endl
		 << endl
		 << "Do you wanna play first?(Y/N)" << endl;
	cin >> inp;
	if (inp != 'Y' && inp != 'y')
	{
		cout << endl
			 << "**My Turn**" << endl;
		Cell bestMove(rand() % 3, rand() % 3);
		makeMove(bestMove, 1);
		printBoard();
	}

	int rc;
	while (true)
	{
		Cell bestMove;
		if (i == 0)
		{
			cout << endl
				 << "**Your Turn**" << endl;
			cin >> x;
			cin >> y;
			if (x < 0 || x >= 3 || y < 0 || y >= 3)
			{
				cout << "Invalid Index! Try again" << endl;
				continue;
			}
			bestMove = Cell(x, y);
		}
		else
		{
			cout << endl
				 << "**My Turn**" << endl;
			bestMove = nextbestMove();
		}

		rc = makeMove(bestMove, i);
		if (-3 == rc)
		{
			cout << "Invalid Index! Try again" << endl;
			continue;
		}
		printBoard();
		if (-2 != rc)
			break;
		i = (i + 1) % 2;
	}

	if (1 == rc)
		cout << endl
			 << "Sorry, You Lost!" << endl;
	else if (-1 == rc)
		cout << endl
			 << "Congrats,You Won!" << endl;
	else
		cout << endl
			 << "Its a Draw!" << endl;
}

}; // namespace tictactoe