#include <iostream>
#include <tictactoe.h>

int main()
{
	tictactoe::TicTacToe newGame;
	newGame.startGame();
	std::cin.get();
	return 0;
}