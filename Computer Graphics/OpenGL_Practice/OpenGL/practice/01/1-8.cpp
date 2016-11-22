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
bool swch{ false };
int tx, ty;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void InputMouse(int button, int state, int x, int y);
void InputMouse(int x, int y);
void InputKeyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

void main(int argc, char *argv[])
{
	int menu;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(Window_Width, Window_Height); // �������� ũ�� ����
	glutCreateWindow("Prac_4"); // ������ ���� (������ �̸�)

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutTimerFunc(100, TimerFunction, 1);
	glutMouseFunc(InputMouse);
	//glutMotionFunc(InputMouse);
	glutKeyboardFunc(InputKeyboard);
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����

	menu = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Rect", Shape_Rect);
	glutAddMenuEntry("Circle", Shape_Circle);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	for (auto p : rcList)
	{
		if (p.GetFlip())glColor4f(1.0f, 0.2f, 0.7f, 1.0f);
		else glColor4f(1.0f, 0.5f, 0.2f, 1.0f);
		p.Print();
	}
	if (swch)
	{
		glColor4f(1.0f, 0.0f, 0.2f, 1.0f);
		glRectf(static_cast<float>(tx) - 10, static_cast<float>(ty) - 10, static_cast<float>(tx) + 10, static_cast<float>(ty) + 10);
	}
	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0f, Window_Width, 0.0f, Window_Height, -1.0, 1.0);
}

void InputMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&& state == GLUT_DOWN)
	{
		for (auto &p : rcList)
		{
			p.SetMove(static_cast<float>(x), static_cast<float>(Window_Height - y), 30.0f);
		}
		swch = true;
		tx = x;
		ty = Window_Height - y;
	}
	if (button == GLUT_LEFT_BUTTON&& state == GLUT_UP)
	{
		for (auto &p : rcList)
		{
			p.SetMove(0.0f, 0.0f, 0.0f);
		}
		swch = false;
	}
	if (button == GLUT_RIGHT_BUTTON&& state == GLUT_UP)
	{
		if (rcList.size() == 20) rcList.pop_front();
		rcList.push_back(CBlock(static_cast<float>(x), static_cast<float>(Window_Height - y), 0.0f, 0.0f, 0.0f, Window_Width, Window_Height, shape, true));
	}
}
void InputMouse(int x, int y)
{
	for (auto &p : rcList)
	{
		p.SetMove(static_cast<float>(x), static_cast<float>(Window_Height - y), 30.0f);
	}
}
void TimerFunction(int value)
{
	for (auto &p : rcList)
	{
		p.Update_eight();
		//p.Flip();
	}


	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
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

/*
�簢�� �̵��ϱ�
������ ��ġ�� ������ ���콺�� Ŭ���Ͽ� �ٸ� ũ���� �簢���� �׸���.
���� ���콺�� Ŭ���ϸ� �� ��ġ�� ���� ũ���� ��ǥ ǥ�ø� �ϰ� ��� �簢������ �� ��ġ�� �̵��Ѵ�
�ٽ� ���� ���콺�� Ŭ���ϸ� ��ǥ ��ġ�� ���ο� ���콺 Ŭ�� ��ġ�� �����Ͽ� �簢������ ��� �̵��Ѵ�.
*/


