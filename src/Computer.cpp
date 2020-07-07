#include "Computer.h"
#include <cstdlib>
#include <algorithm>
#include <cstdlib> //For absolute
#include <iostream>
#include "limits.h"
#include "time.h"
#include "stdlib.h"
#include <random>
#include <map>

map<unsigned long long int, Computer::TTEntry> transpositionTable;

int myrandom (int i){
	srand (time(NULL));
	return std::rand()%i;
}

Computer::Computer(int total, Board *board, int dep){
	m_board = board;
	depth = dep;
	for (int i = 0; i < total; i++)
		Squares.push_back(i);
	random_shuffle(Squares.begin(), Squares.end(), myrandom);
	InitZobrist();
}

int Computer::MakeMoveRandom(int playerVal){

	int current = Squares.back();
	Squares.pop_back();
	while (!(m_board->IsEmptySquare(current)))
	{
		current = Squares.back();
		Squares.pop_back();
	}
	m_board->UpdateBoard(current, playerVal);	
	return current;
}

int Computer::MakeMoveAI(int playerVal){
	double alpha = -99999999999.0;
	double beta = 99999999999.0;
	double lowestMove = AlphaBeta(m_board, depth, alpha, beta, true, playerVal, -1);
	m_board->UpdateBoard(bestMove->GetLastMove(), playerVal);
	return bestMove->GetLastMove();
}

double Computer::Max(double a, double b){
	if (a >= b)
		return a;
	else return b;
}

double Computer::Min(double a, double b){
	if (a <= b)
		return a;
	else return b;
}

double Computer::AlphaBeta(Board *board, int depth, double alpha, double beta, bool maxPlayer, int playerVal, int lastMove){
	if (depth == 0 || board->IsEnd(lastMove, playerVal))
	{
		double heuristicValue = board->GetBoardHeuristicValue();
		return heuristicValue;
	}
	if (maxPlayer)
	{
		double value = -99999999999.0;
		vector<Board*> children;
		children = GenerateChildren(board, playerVal);
		vector<Board*>::iterator it = children.begin();
		for (it; it != children.end(); it++)
		{

			double alphabeta = AlphaBeta((*it), depth - 1, alpha, beta, false, abs(playerVal - 1), (*it)->GetLastMove());
			if (alphabeta > value)
			{
				value = alphabeta;
				bestMove = *it;
			}
			alpha = Max(alpha, value);
			if (alpha > beta)
				{break;}
		}
		return value;
	}
	else
	{
		double value = 99999999999.0;
		vector<Board*> children;
		children = GenerateChildren(board, playerVal);
		vector<Board*>::iterator it = children.begin();
		for (it; it != children.end(); it++)
		{
			double alphabeta = AlphaBeta((*it), depth - 1, alpha, beta, true, abs(playerVal - 1), (*it)->GetLastMove());
			value = Min(value, alphabeta);
			beta = Min(beta, value);
			if (alpha > beta)
				{break;}
		}
		return value;
	}
}

vector<Board*> Computer::GenerateChildren(Board* board, int playerVal){
	vector<Board*> children;	
	for (int i = 0; i < board->GetRows(); i++)
	{
		for (int j = 0; j < board->GetColumns(); j++)
		{
			if (board->GetValue(i, j) == -1)
			{
				Board *child = new Board(board->GetRows(), board->GetColumns(), board->GetToWin());
				for (int k = 0; k < child->GetRows(); k++)
				{
					for (int l = 0; l < child->GetColumns(); l++)
					{child->SetValue(k, l, board->GetValue(k, l));}
				}
				child->SetValue(i, j, playerVal);
				children.push_back(child);
				child->SetLastMove(i*(child->GetColumns())+j);
			}
		}
	}
	return children;
}

int Computer::MakeMoveAITable(int playerVal){
	double alpha = -99999999999.0;
	double beta = 99999999999.0;
	double lowestMove = Negamax(m_board, depth, alpha, beta, true, playerVal, -1);
	m_board->UpdateBoard(bestMove->GetLastMove(), playerVal);
	return bestMove->GetLastMove();
}

double Computer::Negamax(Board *board, int depth, double alpha, double beta, bool maxPlayer, int playerVal, int lastMove){
	double alphaOrigin = alpha;
	TTEntry ttEntry;
	if (IsEntryValid(board))
	{
		ttEntry = TableLookup(board);
		if (ttEntry.depth >= depth)
		{
			if (ttEntry.flag.compare("EXACT") == 0)
				return ttEntry.value;
			else if (ttEntry.flag.compare("LOWERBOUND") == 0)
				alpha = Max(alpha, ttEntry.value);
			else if (ttEntry.flag.compare("UPPERBOUND") == 0)
				beta = Min(beta, ttEntry.value);
			if (alpha >= beta)
				return ttEntry.value;
		}
	}
	if (depth == 0 || board->IsEnd(lastMove, playerVal))
	{
		double heuristicValue = board->GetBoardHeuristicValue();
		return heuristicValue;
	}
double value;
if (maxPlayer)
	{
		value = -99999999999.0;
		vector<Board*> children;
		children = GenerateChildren(board, playerVal);
		vector<Board*>::iterator it = children.begin();
		for (it; it != children.end(); it++)
		{

			double negamax = Negamax((*it), depth - 1, alpha, beta, false, abs(playerVal - 1), (*it)->GetLastMove());
			if (negamax > value)
			{
				value = negamax;
				bestMove = *it;
			}
			alpha = Max(alpha, value);
			if (alpha > beta)
				{break;}
		}
		return value;
	}
	else
	{
		value = 99999999999.0;
		vector<Board*> children;
		children = GenerateChildren(board, playerVal);
		vector<Board*>::iterator it = children.begin();
		for (it; it != children.end(); it++)
		{
			double negamax = Negamax((*it), depth - 1, alpha, beta, true, abs(playerVal - 1), (*it)->GetLastMove());
			value = Min(value, negamax);
			beta = Min(beta, value);
			if (alpha > beta)
				{break;}
		}
	}
	ttEntry.value = value;
	if (value <= alphaOrigin)
		ttEntry.flag = "UPPERBOUND";
	else if (value >= beta)
		ttEntry.flag = "LOWERBOUND";
	else ttEntry.flag = "EXACT";
	ttEntry.depth = depth;
	TableStore(ttEntry, board);
	return value;
}

unsigned long long int Computer::ComputeHash(Board *board){
	unsigned long long int hash = 0;
	for (int i = 0; i < board->GetRows(); i++)
	{
		for (int j = 0; j < board->GetColumns(); j++)
		{
			if (board->GetValue(i, j) != -1)
			{
				int piece = board->GetValue(i, j);
				hash ^= zobristTable[i*(board->GetColumns())+j]->operator[](piece);
			}
		}
	}
	return hash;
}

void Computer::InitZobrist(){
	for (int i = 0; i < ((m_board->GetRows())*(m_board->GetColumns())); i++)
	{
		zobristTable.push_back(new vector<unsigned long long int>());
	}
	for (int i = 0; i < ((m_board->GetRows())*(m_board->GetColumns())); i ++)
	{
		for (int j = 0; j < 2; j++)
			zobristTable[i]->push_back(RandomInt());
	}
}

unsigned long long int Computer::RandomInt(){
	random_device rd;
	mt19937_64 eng(rd());
	uniform_int_distribution<unsigned long long int> dist;
	return dist(eng);
}

Computer::TTEntry Computer::TableLookup(Board *board){
	map<unsigned long long int, Computer::TTEntry>::iterator it;
	it = transpositionTable.find(ComputeHash(board));	
	return (it->second);
}

void Computer::TableStore(TTEntry ttEntry, Board *board){
	transpositionTable.insert(pair<unsigned long long int, Computer::TTEntry>(ComputeHash(board), ttEntry));
}

bool Computer::IsEntryValid(Board *board){
	if (transpositionTable.find(ComputeHash(board)) == transpositionTable.end())
		return false;
	else return true;
}
