#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using std::vector;
using std::endl;
using std::min;
using std::max;
using std::cout;
using std::cin;
using std::pair;


class ticTacToe{

	vector <vector<char>> board;

    public:


		ticTacToe() {
			board = vector<vector<char>>(3, { ' ',' ',' '});
		}



	    int miniMax(vector <vector<char>> board,int flag){
		    int temp = evaluate(board);
		    if (temp == 1) return 1;
		    else if (temp == -1) return -1;
		    else if (temp == 0) return 0;
		    else if (flag == 0){
				int ret = 10;
				for (int i = 0; i < board.size(); i++) {
					for (int j = 0; j < board[i].size(); j++) {
						if (board[i][j] == ' ') {
							board[i][j] = 'O';
							ret =  min(ret,miniMax(board, 1));
							board[i][j] = ' ';}
					}
				}
				return ret;
			}
			else{
				int ret = -10;
				for (int i = 0; i < board.size(); i++) {
					for (int j = 0; j < board[i].size(); j++) {
						if (board[i][j] == ' ') {
							board[i][j] = 'x';
							ret = max(ret, miniMax(board, 0));
							board[i][j] = ' '; 
						}
					}
				}
				return ret;
			}
		    return 0; 
		}



	    int evaluate(vector <vector<char>> board) {
		    //check rows
		    if ((board[0][0] == 'x' && board[0][1] == 'x' && board[0][2] == 'x') ||
			    (board[1][0] == 'x' && board[1][1] == 'x' && board[1][2] == 'x') ||
			    (board[2][0] == 'x' && board[2][1] == 'x' && board[2][2] == 'x'))
			    return 1;
		    if ((board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O') ||
			    (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O') ||
			    (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O'))
			    return -1;

		    //check columns
		    if ((board[0][0] == 'x' && board[1][0] == 'x' && board[2][0] == 'x') ||
			    (board[0][1] == 'x' && board[1][1] == 'x' && board[2][1] == 'x') ||
			    (board[0][2] == 'x' && board[1][2] == 'x' && board[2][2] == 'x'))
			    return 1;
		    if ((board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O') ||
			    (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O') ||
			    (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O'))
			    return -1;

		    //check diagonals
		    if ((board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x') ||
			    (board[0][2] == 'x' && board[1][1] == 'x' && board[2][0] == 'x'))
			    return 1;
		    if ((board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') ||
			    (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O'))
			    return -1;

		    //If board is full, return 0 else return -2
		    for (int i = 0; i < board.size(); i++) {
			    for (int j = 0; j < board[i].size(); j++) {
				    if (board[i][j] == ' ') return -2; 
				}
			}
		    return 0; 
		}



	    pair<int,int> nextbestMove(){
		    int ret = -10, temp, iBest = -1, jBest = -1;
		    for (int i = 0; i < board.size(); i++) {			
			    for (int j = 0; j < board[i].size(); j++){
				    if (board[i][j] == ' '){
					    board[i][j] = 'x';
					    temp = miniMax(board,0);
					    if (temp > ret){
						    iBest = i;
						    jBest = j;
						    ret = temp;
						}
					    board[i][j] = ' '; 
					}
				}
			}
		    return pair<int, int>(iBest, jBest); 
		}



	    void printBoard(){
		    for (int i = 0; i < 3; i++){
			    if (i == 0) {
				    cout << " ";
				    for (int j = 0; j < 3; j++) cout << "___" << " ";
				    cout << endl;
			    }
			    else {
				    cout << "|";
				    for (int j = 0; j < 3; j++) cout << "___" << "|";
				    cout << endl;
			    }			
			    cout<< "|";
			    for (int j = 0; j < 3; j++) cout <<" "<< board[i][j] <<" "<<"|";
			    cout << endl; 
		    }
		    cout << "|";
		    for (int i = 0; i<3; i++) cout <<"___" << "|";
		    cout << endl;
		    return; 
		}



	    int makeMove(pair<int,int> bestMove,int flag){
			if (board[bestMove.first][bestMove.second] != ' ') return -3;
		    if (flag == 0) board[bestMove.first][bestMove.second] = 'O';
		    else board[bestMove.first][bestMove.second] = 'x';
		    return evaluate(board); 
		}



		void startGame() {
			srand(time(nullptr));
			int x, y, temp,i=0;
			char inp;
			cout << "Welcome Opponent! You are 'O' and I am 'x'. Sorry, no options here."<<endl
				 << "But I will let you play first if you want. " << endl << endl
				 << "Do you wanna play first?(Y/N)" << endl;
			cin >> inp;
			if (inp != 'Y' && inp != 'y') {
				cout << endl << "**My Turn**" << endl;
				pair<int, int> bestMove(rand()%3,rand()%3);
				temp = makeMove(bestMove, 1);
				printBoard();
			}

			while (true) {
				pair<int, int> bestMove;
				if (i == 0) {
					cout << endl << "**Your Turn**" << endl;
					cin >> x; cin >> y;
					if (x <0 || x >= 3 || y<0 || y >= 3) { cout << "Invalid Index! Try again" << endl; continue; }
					bestMove = pair<int, int>(x, y);
				}
				else {
					cout << endl << "**My Turn**" << endl;
					bestMove = nextbestMove();
				}
				temp = makeMove(bestMove, i);
				if(temp==-3) { cout << "Invalid Index! Try again" << endl; continue; }
				printBoard();
				if (temp != -2) break;
				i = (i + 1) % 2;
			}

			if (temp == 1) cout << endl << "Sorry, You Lost!" << endl;
			else if (temp == -1) cout << endl << "Congrats,You Won!" << endl;
			else cout << endl << "Its a Draw!" << endl;
		}
};



int main(){	
	ticTacToe *newGame = new ticTacToe();
	newGame->startGame();
	delete newGame;
	cin.get();
	cin.get();
	return 0;
}