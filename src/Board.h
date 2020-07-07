/**
 *@brief Project_3 CSC547
 *@author Tien Pham
 */

#ifndef BOARD_H_INCLUDE
#define BOARD_H_INCLUDE

#include <vector>

using namespace std;

class Board{
	public:
	Board(int rows, int columns, int toWin);
	bool IsEnd(int lastMove, int playerVal);
	bool IsEmptySquare(int square);
	void UpdateBoard(int current, int playerVal);
	double GetBoardHeuristicValue();
	
int GetValue(int r, int c)
{
return myBoard[r]->operator[](c);
//return (*(myBoard[r]))[c];
}

void SetValue(int r, int c, int val)
{
myBoard[r]->operator[](c) = val;
}

int GetLastMove(){
	return lastMove;
}

void SetLastMove(int i){
	lastMove = i;
}

int GetRows(){
	return Rows;
}

int GetColumns(){
	return Columns;
}

int GetToWin(){
	return ToWin;
}

vector<vector<int>* >GetBoard(){
	return myBoard;
}

int GetWinner(){
	return winner;
}

	protected:
	
	private:
	void InitCurrentSquare(int *currentSquare, int *currentRow, int *currentCol, int lastMove);
	int Rows, Columns, ToWin;
	int lastMove;
	vector<vector<int>* > myBoard; //"O" = 0, "X" = 1, Empty = -1;
	int winner;
	
};

#endif
