/**
 *@brief Project_3 CSC547
 *@author Tien Pham
 */

#ifndef COMPUTER_H_INCLUDE
#define COMPUTER_H_INCLUDE

#include "Board.h"
#include <string>
#include <vector>

using namespace std;

class Computer{
	public:
	Computer(int total, Board *board, int depth);
	int MakeMoveRandom(int playerVal);
	int MakeMoveAI(int playerVal);
	int MakeMoveAITable(int playerVal);
	struct TTEntry{
		double value;
		int depth;
		string flag;
	};
	protected:

	private:
	vector<int> Squares;
	Board *m_board;
	Board *bestMove;
	int depth;
	double Max(double a, double b);
	double Min(double a, double b);
	double AlphaBeta(Board *board, int depth, double alpha, double beta, bool maxPlayer, int playerVal, int lastMove);
	double Negamax(Board *board, int depth, double alpha, double beta, bool maxPlayer, int playerVal, int lastMove);
	vector<Board*> GenerateChildren(Board *board, int playerVal);
	vector<vector<unsigned long long int>* > zobristTable;
	unsigned long long int ComputeHash(Board* board);
	unsigned long long int RandomInt();
	bool IsEntryValid(Board* board);
	TTEntry TableLookup(Board *board);
	void TableStore(TTEntry ttEntry, Board *board);
	void InitZobrist();
	
};

#endif
