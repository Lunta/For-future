/*
임의의 도형 그리기
화면을 9등분한다.
화면의 첫 칸에 아래의 도형 중 한 개의 도형을 그린다.
선 삼각형, 사각형, 오각형
다음 칸부터 도형의 꼭짓점이 한 개씩 늘어나게 그리고, 오각혀 후에는 다시 선으로 그린다
선, 삼각형 사각형 오각형 ,선

*/
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
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example3");
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정
	glutMainLoop(); // 이벤트
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기

	int n = rand() % 4;
	
	float r1 = rand() % 100, g1 = rand() % 100, b1 = rand() % 100;
	float r2 = rand() % 100, g2 = rand() % 100, b2 = rand() % 100;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if((i + j) % 2)glColor4f(r1 / 100, g1 / 100, b1 / 100, 1.0f);
			else glColor4f(r2 / 100, g2 / 100, b2 / 100, 1.0f);
			glRectf(-400.0f + ((800.0f / 3.0f) * j), 300.0f - ((600.0f / 3.0f) * i),
				-400.0f + ((800.0f / 3.0f) * (j + 1)), 300.0f - ((600.0f / 3.0f) * (i + 1)));

			glColor4f(1.0f, 0.2f, 0.7f, 1.0f);
			glLineWidth(3.0f);
		
			switch (n)
			{
			case 0:
				glBegin(GL_LINES);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) + 100.0f, 200.0f - ((600.0f / 3.0f) * i) + 70.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) - 80.0f, 200.0f - ((600.0f / 3.0f) * i) - 80.0f);
				break;
			case 1:
				glBegin(GL_POLYGON);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) - 50.0f, 200.0f - ((600.0f / 3.0f) * i) + 50.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) + 100.0f, 200.0f - ((600.0f / 3.0f) * i) + 70.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) - 80.0f, 200.0f - ((600.0f / 3.0f) * i) - 80.0f);
				break;
			case 2:
				glBegin(GL_POLYGON);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) - 50.0f, 200.0f - ((600.0f / 3.0f) * i) + 50.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) + 100.0f, 200.0f - ((600.0f / 3.0f) * i) + 70.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) + 50.0f, 200.0f - ((600.0f / 3.0f) * i) - 50.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) - 50.0f, 200.0f - ((600.0f / 3.0f) * i) - 50.0f);
				break;
			case 3:
				glBegin(GL_POLYGON);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) - 50.0f, 200.0f - ((600.0f / 3.0f) * i) + 50.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) + 100.0f, 200.0f - ((600.0f / 3.0f) * i) + 70.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) + 100.0f, 200.0f - ((600.0f / 3.0f) * i) - 25.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) + 50.0f, 200.0f - ((600.0f / 3.0f) * i) - 70.0f);
				glVertex2f(-300.0f + ((800.0f / 3.0f) * j) - 80.0f, 200.0f - ((600.0f / 3.0f) * i) - 60.0f);
				break;
			}
			++n %= 4;
			glEnd();
		}
	}
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}