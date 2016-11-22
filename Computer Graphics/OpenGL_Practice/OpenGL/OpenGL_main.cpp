#include "stdafx.h"
#include "Framework.h"

namespace {

	CFramework myframework;

};// 익명 namespace => 해당 cpp에서만 사용가능

void main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(CLIENT_XPOS, CLIENT_YPOS); // 윈도우의 위치지정
	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT); // 윈도우의 크기 지정
	glutCreateWindow(TITLESTRING); // 윈도우 생성 (윈도우 이름)

	myframework.OnCreate(CLIENT_WIDTH, CLIENT_HEIGHT);
	
	glutDisplayFunc(CFramework::OnDraw); // 출력 함수의 지정
	glutTimerFunc(0, CFramework::FrameAdvance, MAINGAMELOOP_ID);
	glutMouseFunc(CFramework::InputMouse);
	glutKeyboardFunc(CFramework::InputKeyboard);
	glutReshapeFunc(CFramework::Reshape); // 다시 그리기 함수의 지정
	
	glutMainLoop();
}