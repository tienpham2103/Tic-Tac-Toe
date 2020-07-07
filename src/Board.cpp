#include "Board.h"
#include <iostream>

Board::Board(int rows, int columns, int toWin){
	Rows = rows;
	Columns = columns;
	ToWin = toWin;
	winner = -1;
	for (int i = 0; i < Rows; i++)
		myBoard.push_back(new vector<int>());
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			myBoard[i]->push_back(-1);
		}
	}
}

bool Board::IsEnd(int lastMove, int playerVal){
	if (lastMove == -1)
		return false;
	bool draw = true;
	int currentSquare, currentRow, currentCol;
	int count = 1;
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	for (int i = 1; i < ToWin; i++)
	{
		if (currentSquare - Columns >= 0 && GetValue(currentRow - 1, currentCol) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns);
		}
		else break;
	}
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	for (int i = 1; i < ToWin; i++)
	{
		if (currentSquare + Columns < Rows*Columns && GetValue(currentRow + 1,currentCol) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns);
		}
		else break;
	}
	if (count >= ToWin)
		{winner = playerVal; cout << "Winner: Player " << winner << endl; return true;}
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	count = 1;
	for (int i = 1; i < ToWin; i++)
	{
		if (currentSquare + 1 < Rows*Columns && currentRow == ((currentSquare+1)/Columns) && GetValue(currentRow, currentCol + 1) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + 1);
		}
		else break;
	}
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	for (int i = 1; i < ToWin; i++)
	{
		if (currentSquare - 1 >= 0 && currentRow == ((currentSquare-1)/Columns) && GetValue(currentRow, currentCol - 1) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - 1);
		}
		else break;
	}
	if (count >= ToWin)
		{winner = playerVal; cout << "Winner: Player " << winner << endl; return true;}
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	count = 1;
	for (int i = 1; i < ToWin; i++)
	{
		if ((currentSquare - Columns - 1) >= 0 && (currentRow - (currentSquare - Columns - 1)/Columns) == 1 && GetValue(currentRow - 1, currentCol - 1) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns - 1);
		}
		else break;
	}
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	for (int i = 1; i < ToWin; i++)
	{
		if ((currentSquare + Columns + 1) < Rows*Columns && (-currentRow + (currentSquare + Columns + 1)/Columns) == 1 && GetValue(currentRow + 1, currentCol + 1) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns + 1);
		}
		else break;
	}
	if (count >= ToWin)
		{winner = playerVal; cout << "Winner: Player " << winner << endl; return true;}
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	count = 1;
	for (int i = 1; i < ToWin; i++)
	{
		if ((currentSquare - Columns + 1) >= 0 && (currentRow - (currentSquare - Columns + 1)/Columns) == 1 && GetValue(currentRow - 1, currentCol + 1) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns + 1);
		}
		else break;
	}
	InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
	for (int i = 1; i < ToWin; i++)
	{
		if ((currentSquare + Columns - 1) < Rows*Columns && (-currentRow + (currentSquare + Columns - 1)/Columns) == 1 && GetValue(currentRow + 1, currentCol - 1) == playerVal)
		{
			count++;
			InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns - 1);
		}		
		else break;
	}
	if (count >= ToWin)
		{winner = playerVal; cout << "Winner: Player " << winner << endl; return true;}
	for (int i = 0; i < Rows; i++)
	{
		bool flag = false;
		for (int j = 0; j < Columns; j++)
		{
			if (GetValue(i, j) == -1)
			{draw = false; flag = true; break;}
		}
		if (flag)
			break;
	}
	if (draw == true)
	{winner = 2; cout << "Draw!" << endl; return true;}
	return false;
}

bool Board::IsEmptySquare(int current){
	if (GetValue(current/Columns, current%Columns) == -1)
		return true;
	else return false;
}

void Board::UpdateBoard(int current, int playerVal){
	SetValue(current/Columns, current%Columns, playerVal);
}

void Board::InitCurrentSquare(int *currentSquare, int *currentRow, int *currentCol, int lastMove){
	*currentSquare = lastMove;
	*currentRow = lastMove/Columns;
	*currentCol = lastMove%Columns;
}

double Board::GetBoardHeuristicValue(){
	if (winner == 1)
		{return 1000;}
	else if (winner == 0)
		{return -1000;}	
	double heuristicScore = 0.0;
	double player1Score = 0.0;
	double player2Score = 0.0;
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (GetValue(i, j) == -1)
				continue;
			else if (GetValue(i, j) == 1)
			{
				int lastMove = i*Columns + j;
				int currentSquare, currentRow, currentCol;
				bool flag = false;
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
				for (int k = 1; k < ToWin; k++)
				{
					if (currentSquare - Columns >= 0 )
					{
						if (flag == true && (GetValue(currentRow - 1, currentCol) == 1 || GetValue(currentRow - 1, currentCol) == -1))
							{break;}
						if (GetValue(currentRow - 1, currentCol) == 1)
							{player1Score += 4*k;}
						else if (GetValue(currentRow - 1, currentCol) == -1)
							{player1Score += 2*k;}
						else 
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else {player1Score += 6*k;}
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if (currentSquare + Columns < Rows*Columns)
					{
						if (flag == true && (GetValue(currentRow + 1, currentCol) == 1 || GetValue(currentRow + 1, currentCol) == -1))
							break;
						if (GetValue(currentRow + 1, currentCol) == 1)
							player1Score += 4*k;
						else if (GetValue(currentRow + 1, currentCol) == -1)
							player1Score += 2*k;
						else 
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else player1Score += 6*k;
						}
					InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if (currentRow == ((currentSquare+1)/Columns))
					{
						if (flag == true && (GetValue(currentRow, currentCol + 1) == 1 || GetValue(currentRow, currentCol + 1) == -1))
							break;
						if (GetValue(currentRow, currentCol + 1) == 1)
							player1Score += 4*k;
						else if (GetValue(currentRow, currentCol + 1) == -1)
							player1Score += 2*k;
						else 
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else player1Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if (currentSquare - 1 >= 0 && currentRow == ((currentSquare-1)/Columns))
					{
						if (flag == true && (GetValue(currentRow, currentCol - 1) == 1 || GetValue(currentRow, currentCol - 1) == -1))
							break;
						if (GetValue(currentRow, currentCol - 1) == 1)
							player1Score += 4*k;
						else if (GetValue(currentRow, currentCol - 1) == -1)
							player1Score += 2*k;
						else 
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else player1Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare - Columns - 1) >= 0 && (currentRow - (currentSquare - Columns - 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow - 1, currentCol - 1) == 1 || GetValue(currentRow - 1, currentCol - 1) == -1))
							break;
						if (GetValue(currentRow - 1, currentCol - 1) == 1)
							player1Score += 4*k;
						else if (GetValue(currentRow - 1, currentCol - 1) == -1)
							player1Score += 2*k;
						else 
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else player1Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns - 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare + Columns + 1) < Rows*Columns && (-currentRow + (currentSquare + Columns + 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow + 1, currentCol + 1) == 1 || GetValue(currentRow + 1, currentCol + 1) == -1))
							break;
						if (GetValue(currentRow + 1, currentCol + 1) == 1)
							player1Score += 4*k;
						else if (GetValue(currentRow + 1, currentCol + 1) == -1)
							player1Score = player1Score + 2*k;
						else 
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else player1Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns + 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare - Columns + 1) >= 0 && (currentRow - (currentSquare - Columns + 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow - 1, currentCol + 1) == 1 || GetValue(currentRow - 1, currentCol + 1) == -1))
							break;
						if (GetValue(currentRow - 1, currentCol + 1) == 1)
							{player1Score += 4*k;}
						else if (GetValue(currentRow - 1, currentCol + 1) == -1)
							{player1Score += 2*k;}
						else 
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else player1Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns + 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare + Columns - 1) < Rows*Columns && (-currentRow + (currentSquare + Columns - 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow + 1, currentCol - 1) == 1 || GetValue(currentRow + 1, currentCol - 1) == -1))
							break;
						if (GetValue(currentRow + 1, currentCol - 1) == 1)
							player1Score += 4*k;
						else if (GetValue(currentRow + 1, currentCol - 1) == -1)
							player1Score += 2*k;
						else 	
						{	
							if (flag == false)
							{player1Score -= (4*ToWin)/k; flag = true;}
							else player1Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns - 1);
					}		
					else break;
				}
			}
			else
			{
				int lastMove = i*Columns + j;
				int currentSquare, currentRow, currentCol;
				bool flag = false;
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);
				for (int k = 1; k < ToWin; k++)
				{
					if (currentSquare - Columns >= 0)
					{
						if (flag == true && (GetValue(currentRow - 1, currentCol) == 0 || GetValue(currentRow - 1, currentCol) == -1))
							break;
						if (GetValue(currentRow - 1, currentCol) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow - 1, currentCol) == -1)
							player2Score += 2*k;
						else 
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if (currentSquare + Columns < Rows*Columns)
					{
						if (flag == true && (GetValue(currentRow + 1, currentCol) == 0 || GetValue(currentRow + 1, currentCol) == -1))
							break;
						if (GetValue(currentRow + 1, currentCol) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow + 1, currentCol) == -1)
							player2Score += 2*k;
						else
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
					InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if (currentRow == ((currentSquare+1)/Columns))
					{
						if (flag == true && (GetValue(currentRow, currentCol+1) == 0 || GetValue(currentRow, currentCol+1) == -1))
							break;
						if (GetValue(currentRow, currentCol + 1) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow, currentCol + 1) == -1)
							player2Score += 2*k;
						else
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if (currentSquare - 1 >= 0 && currentRow == ((currentSquare-1)/Columns))
					{
						if (flag == true && (GetValue(currentRow, currentCol-1) == 0 || GetValue(currentRow, currentCol-1) == -1))
							break;
						if (GetValue(currentRow, currentCol - 1) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow, currentCol - 1) == -1)
							player2Score += 2*k;
						else
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare - Columns - 1) >= 0 && (currentRow - (currentSquare - Columns - 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow-1, currentCol-1) == 0 || GetValue(currentRow-1, currentCol-1) == -1))
							break;
						if (GetValue(currentRow - 1, currentCol - 1) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow - 1, currentCol - 1) == -1)
							player2Score += 2*k;
						else
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns - 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare + Columns + 1) < Rows*Columns && (-currentRow + (currentSquare + Columns + 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow+1, currentCol+1) == 0 || GetValue(currentRow+1, currentCol+1) == -1))
							break;
						if (GetValue(currentRow + 1, currentCol + 1) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow + 1, currentCol + 1) == -1)
							player2Score += 2*k;
						else
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns + 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare - Columns + 1) >= 0 && (currentRow - (currentSquare - Columns + 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow-1, currentCol+1) == 0 || GetValue(currentRow-1, currentCol+1) == -1))
							break;
						if (GetValue(currentRow - 1, currentCol + 1) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow - 1, currentCol + 1) == -1)
							player2Score += 2*k;
						else
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare - Columns + 1);
					}
					else break;
				}
				InitCurrentSquare(&currentSquare, &currentRow, &currentCol, lastMove);flag = false;
				for (int k = 1; k < ToWin; k++)
				{
					if ((currentSquare + Columns - 1) < Rows*Columns && (-currentRow + (currentSquare + Columns - 1)/Columns) == 1)
					{
						if (flag == true && (GetValue(currentRow+1, currentCol-1) == 0 || GetValue(currentRow+1, currentCol-1) == -1))
							break;
						if (GetValue(currentRow + 1, currentCol - 1) == 0)
							player2Score += 4*k;
						else if (GetValue(currentRow + 1, currentCol - 1) == -1)
							player2Score += 2*k;
						else
						{	
							if (flag == false)
							{player2Score -= (4*ToWin)/k; flag = true;}
							else player2Score += 6*k;
						}
						InitCurrentSquare(&currentSquare, &currentRow, &currentCol, currentSquare + Columns - 1);
					}		
					else break;
				}
			}
		}
	}
	heuristicScore = player1Score - player2Score;
	return heuristicScore;
}
