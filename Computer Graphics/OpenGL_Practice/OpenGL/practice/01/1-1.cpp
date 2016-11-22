#include<GL/glut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example1");
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop(); // �̺�Ʈ
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear ( GL_COLOR_BUFFER_BIT ); // ������ ������ ��ü�� ĥ�ϱ�

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

	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	//glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}