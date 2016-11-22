#include "stdafx.h"
#include "Framework.h"

namespace {

	CFramework myframework;

};// �͸� namespace => �ش� cpp������ ��밡��

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(CLIENT_XPOS, CLIENT_YPOS); // �������� ��ġ����
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT); // �������� ũ�� ����
	glutCreateWindow(TITLESTRING); // ������ ���� (������ �̸�)

	myframework.OnCreate(CLIENT_WIDTH, CLIENT_HEIGHT);
	
	glutDisplayFunc(CFramework::OnDraw); // ��� �Լ��� ����
	glutTimerFunc(0, CFramework::FrameAdvance, MAINGAMELOOP_ID);
	glutMouseFunc(CFramework::InputMouse);
	glutKeyboardFunc(CFramework::InputKeyboard);
	glutReshapeFunc(CFramework::Reshape); // �ٽ� �׸��� �Լ��� ����
	
	glutMainLoop();
}