#include "TTT.h"
#include <iostream>
#include <cmath>
#include <GL/glut.h>

const float WINDOW_HEIGHT = 600;
const float WINDOW_WIDTH = 600;
TTT *m_graphics = NULL;

TTT::TTT(int rows, int cols, int toWin, string p1Type, string p2Type, int depth){
	Rows = rows;
	Columns = cols;
	ToWin = toWin;
	Player1 = p1Type;
	Player2 = p2Type;
	Depth = depth;

   	m_board = new Board(rows, cols, toWin);
	m_computer = new Computer(Rows*Columns, m_board, depth);
}

void TTT::Run(){
	if (Player1.compare("human") == 0 && Player2.compare("human") != 0)
		GameType = 1;
	else if (Player1.compare("human") != 0 && Player2.compare("human") == 0)
		GameType = 2;
	else if (Player1.compare("human") == 0 && Player2.compare("human") == 0)
		GameType = 3;
	else GameType = 4;
	MainLoop();
}

void TTT::MainLoop(){
	m_graphics = this;
	static int argc = 1;
	static char *args = (char*)"args";
	glutInit(&argc, &args);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Tic-Tac-Toe");

	glutDisplayFunc(CallbackEventOnDisplay);
	glutMouseFunc(CallbackEventOnMouse);

	//Enter main event loop
	glutMainLoop();
}

void TTT::CallbackEventOnDisplay(){
	if (m_graphics)
	{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_graphics->HandleEventOnDisplay();
	glutPostRedisplay();
	glutSwapBuffers();
	}
}

void TTT::MousePosition(const int x, const int y, double *posX, double *posY){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, posX, posY, &posZ);
}

void TTT::CallbackEventOnMouse(int button, int state, int x, int y){
	if (m_graphics && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		MousePosition(x, y, &(m_graphics->MouseX), &(m_graphics->MouseY));
		m_graphics -> HandleEventOnMouseLeftButtonDown();
		glutPostRedisplay();
	}
}

void TTT::HandleEventOnMouseLeftButtonDown(){	
	int current;
	if (GameType == 1)
	{
		if (ClickCount == 0)
		{
			current = floor(MouseY*Rows/WINDOW_HEIGHT)*Columns + floor(MouseX*Columns/WINDOW_WIDTH);
			PositionX.push_back(current);
			m_board->UpdateBoard(current, 1);
			if (m_board->IsEnd(current, 1))
			{
				printf("Game over!\n");			
			}
			ClickCount = 1;
		}
		else
		{
			if (Player2.compare("random") == 0)
			{
				current = m_computer->MakeMoveRandom(0);
				PositionO.push_back(current);
			}
			else if (Player2.compare("AI") == 0)
			{
				current = m_computer->MakeMoveAI(0);
				PositionO.push_back(current);
			}
			else 
			{
				current = m_computer->MakeMoveAITable(0);
				PositionO.push_back(current);
			}
			if (m_board->IsEnd(current, 0))
			{
				printf("Game over!\n");
			}
			ClickCount = 0;
		}
	}
	else if (GameType == 2)
	{
		if (ClickCount == 0)
		{
			if (Player1.compare("random") == 0)
			{
				current = m_computer->MakeMoveRandom(1);
				PositionX.push_back(current);
			}
			else if (Player1.compare("AI") == 0)
			{
				current = m_computer->MakeMoveAI(1);
				PositionX.push_back(current);
			}
			else
			{
				current = m_computer->MakeMoveAITable(1);
				PositionX.push_back(current);
			}
			if (m_board->IsEnd(current, 1))
			{
				cout << "Game over!" << endl;
			}
			ClickCount = 1;
		}
		else
		{
			current = floor(MouseY*Rows/WINDOW_HEIGHT)*Columns + floor(MouseX*Columns/WINDOW_WIDTH);
			PositionO.push_back(current);
			m_board->UpdateBoard(current, 0);
			if (m_board->IsEnd(current, 0))
			{
				cout << "Game over!" << endl;
			}
			ClickCount = 0;
		}
	}
	else if (GameType == 3)
	{
		if (ClickCount == 0)
		{
			current = floor(MouseY*Rows/WINDOW_HEIGHT)*Columns + floor(MouseX*Columns/WINDOW_WIDTH);
			PositionX.push_back(current);
			m_board->UpdateBoard(current, 1);
			if (m_board->IsEnd(current, 1))
			{
				printf("Game over!\n");
			}
			ClickCount = 1;
		}
		else
		{
			current = floor(MouseY*Rows/WINDOW_HEIGHT)*Columns + floor(MouseX*Columns/WINDOW_WIDTH);
			PositionO.push_back(current);
			m_board->UpdateBoard(current, 0);
			if (m_board->IsEnd(current, 0))
			{
				printf("Game over!\n");
			}
			ClickCount = 0;
		}
	}
	else
	{
		if (ClickCount == 0)
		{
			if (Player1.compare("random") == 0)
			{
				current = m_computer->MakeMoveRandom(1);
				PositionX.push_back(current);
			}
			else if (Player1.compare("AI") == 0)
			{
				current = m_computer->MakeMoveAI(1);
				PositionX.push_back(current);
			}
			else
			{
				current = m_computer->MakeMoveAITable(1);
				PositionX.push_back(current);
			}
			if (m_board->IsEnd(current, 1))
			{
				cout << "Game over!" << endl;;
			}
			ClickCount = 1;
		}
		else
		{
			if (Player2.compare("random") == 0)
			{
				current = m_computer->MakeMoveRandom(0);
				PositionO.push_back(current);
			}
			else if (Player2.compare("AI") == 0)
			{
				current = m_computer->MakeMoveAI(0);
				PositionO.push_back(current);
			}
			else
			{
				current = m_computer->MakeMoveAITable(0);
				PositionO.push_back(current);
			}
			if (m_board->IsEnd(current, 0))
			{
				cout << "Game over!" << endl;
			}
			ClickCount = 0;
		}
	}
}

void TTT::HandleEventOnDisplay(){
	if (!PositionX.empty())
	{
		vector<int>::iterator it = PositionX.begin();
		for (it; it != PositionX.end(); it++)
		{
			DrawX(*it);
		}
	}
	if (!PositionO.empty())
	{
		vector<int>::iterator it = PositionO.begin();
		for (it; it != PositionO.end(); it++)
		{
			DrawO(*it);
		}
	}
	DrawBoard();
}

void TTT::DrawBoard(){
	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (float i = 1; i < Rows; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(0, WINDOW_HEIGHT*(i/Rows));
		glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT*(i/Rows));
		glEnd();
	}
	for (float i = 1; i < Columns; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(WINDOW_WIDTH*(i/Columns), 0);
		glVertex2f(WINDOW_WIDTH*(i/Columns), WINDOW_HEIGHT);
		glEnd();
	}
}

void TTT::DrawX(int X){
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(WINDOW_WIDTH*((double)(X%Columns)/Columns), WINDOW_HEIGHT*((double)(X/Columns)/Columns));
	glVertex2f(WINDOW_WIDTH*((double)(X%Columns + 1)/Columns), WINDOW_HEIGHT*((double)(X/Columns)/Columns));
	glVertex2f(WINDOW_WIDTH*((double)(X%Columns + 1)/Columns), WINDOW_HEIGHT*((double)(X/Columns + 1)/Columns));
	glVertex2f(WINDOW_WIDTH*((double)(X%Columns)/Columns), WINDOW_HEIGHT*((double)(X/Columns + 1)/Columns));
	glEnd();
}

void TTT::DrawO(int O){
	glColor3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2f(WINDOW_WIDTH*((double)(O%Columns)/Columns), WINDOW_HEIGHT*((double)(O/Columns)/Columns));
	glVertex2f(WINDOW_WIDTH*((double)(O%Columns + 1)/Columns), WINDOW_HEIGHT*((double)(O/Columns)/Columns));
	glVertex2f(WINDOW_WIDTH*((double)(O%Columns + 1)/Columns), WINDOW_HEIGHT*((double)(O/Columns + 1)/Columns));
	glVertex2f(WINDOW_WIDTH*((double)(O%Columns)/Columns), WINDOW_HEIGHT*((double)(O/Columns + 1)/Columns));
	glEnd();
}

int main(int argc, char **argv){
	if (argc < 7)
	{
		printf("Missing input arguments.\n");
		printf("TTT <#Rows> <#Columns> <#toWin> <player1Type> <player2Type> <depth>");
		return 0;
	}
	
	TTT ttt(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], atoi(argv[6]));
	ttt.Run();	
	return 0;
}
