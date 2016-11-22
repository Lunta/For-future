#include<GL/glut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop(); // 이벤트
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear ( GL_COLOR_BUFFER_BIT ); // 설정된 색으로 젂체를 칠하기

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 
	glRectf(-0.25f, -0.25f, 0.25f, 0.25f); 

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); 
	glRectf(-1.0f, -1.0f, -0.5f, -0.5f);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); 
	glRectf(-1.0f, 1.0f, -0.5f, 0.5f);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); 
	glRectf(1.0f, -1.0f, 0.5f, -0.5f);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); 
	glRectf(1.0f, 1.0f, 0.5f, 0.5f);

	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}