#include<Windows.h>
#include<iostream>
#include <chrono>
#include<list>
#include"Block.h"

constexpr float Window_Width = 800.0f;
constexpr float Window_Height = 600.0f;
constexpr int Shape_Rect = 1;
constexpr int Shape_Circle = 2;

std::list <CBlock> rcList;
std::list<CBlock>::iterator itor = rcList.begin();
int shape = Shape_Rect;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void InputMouse(int button, int state, int x, int y);
void InputKeyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

void main(int argc, char *argv[])
{
	int menu;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정
	glutCreateWindow("Prac_4"); // 윈도우 생성 (윈도우 이름)

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutTimerFunc(100, TimerFunction, 1);
	glutMouseFunc(InputMouse);
	glutKeyboardFunc(InputKeyboard);
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정

	menu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry( "Rect", Shape_Rect);
	glutAddMenuEntry("Circle", Shape_Circle);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	for (auto p : rcList)
	{
		if (p.GetFlip())glColor4f(1.0f, 0.2f, 0.7f, 1.0f);
		else glColor4f(1.0f, 0.5f, 0.2f, 1.0f);
		p.Print();
	}
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0f, Window_Width, 0.0f, Window_Height, -1.0, 1.0);
}

void InputMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&& state == GLUT_UP)
	{
		float vx = (rand() % 100)*(0.01f);
		float vy = 1 - vx;
		if (rand() % 2) vx = -vx;
		if (rand() % 2) vy = -vy;
		if (rcList.size() == 20) rcList.pop_front();
		rcList.push_back(CBlock(static_cast<float>(x), static_cast<float>(Window_Height - y), vx, vy , 10.0f, Window_Width, Window_Height, shape, false));
	}
	if (button == GLUT_RIGHT_BUTTON&& state == GLUT_UP)
	{

	}
}
void TimerFunction(int value)
{
	for (auto &p : rcList)
	{
		p.Update_five();
		p.Flip();
	}


	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void InputKeyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
		for (auto &p : rcList)
		{
			p.Fast();
		}
	if (key == 's')
		for (auto &p : rcList)
		{
			p.Slow();
		}
}

void MenuFunc(int button)
{
	switch (button)
	{
	case Shape_Rect: 
		shape = Shape_Rect;
		break;
	case Shape_Circle:
		shape = Shape_Circle;
		break;
	}
}
