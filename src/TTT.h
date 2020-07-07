/**
 *@brief Project_3 CSC547
 *@author Tien Pham
 */

#ifndef TTT_H_INCLUDE
#define TTT_H_INCLUDE

#include <string>
#include "Computer.h"
#include <vector>

using namespace std;

class TTT{
	public:
	TTT(int rows, int cols, int toWin, string p1Type, string p2Type, int depth);
	void Run();

	protected:
	
	void HandleEventOnDisplay();
	void HandleEventOnMouseLeftButtonDown();
	static void CallbackEventOnDisplay();
	static void CallbackEventOnMouse(int button, int state, int x, int y);
	static void MousePosition(const int x, const int y, double *posX, double *posY);

	void DrawBoard();
	void DrawX(int X);
	void DrawO(int O);

	private:
	Board *m_board;
	Computer *m_computer;
	int Rows, Columns, ToWin, Depth;
	string Player1, Player2;
	int GameType;
	int ClickCount = 0;
	double MouseX, MouseY;
	vector<int> PositionX;
	vector<int> PositionO;

	void MainLoop();

};

#endif
