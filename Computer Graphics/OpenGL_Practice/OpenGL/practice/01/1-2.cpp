#include<GL/glut.h>
#include<iostream>
#include<time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ��� ����
	glutMainLoop(); // �̺�Ʈ
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	int n = rand() % 19 + 2;
	float r1 = rand() % 100, g1 = rand() % 100, b1 = rand() % 100;
	float r2 = rand() % 100, g2 = rand() % 100, b2 = rand() % 100;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((i + j) % 2) glColor4f(r1 / 100, g1 / 100, b1 / 100, 1.0f); 
			else glColor4f(r2 / 100, g2 / 100, b2 / 100, 1.0f);

			glRectf(-400.0f + ((800.0f / n) * j), -300.0f + ((600.0f / n) * i),
				-400.0f + ((800.0f / n) * (j + 1)), -300.0f + ((600.0f / n) * (i + 1)));
		}
	}
	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}