#pragma once
#include "Practice.h"

struct torus
{
	float rad = 0.0f;
	float y = 150.0f;
	bool stop = false;
	int num = 0;
	torus(int n) { num = n; }
	void rendering()
	{
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(10.0f*cosf(rad), 10.0f*sinf(rad), y);
		glutWireTorus(15.0f, 45.0f, 10, 10);
		glPopMatrix();
	}
	void update(float fTimeElapsed)
	{
		if (stop) return;
		y -= 50.0f * fTimeElapsed;
		rad += 15.0f * fTimeElapsed;
		if (-35.0f + num * 30.0f > y) stop = true;
	}
};

struct surface
{
	float rad = 0.0f;
	float y = 150.0f;
	bool stop = false;
	int num = 0;
	surface(int n) { num = n; }
	void rendering()
	{
		glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glRotatef(rad, 0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3f(-70.0f, y, 70.0f);
		glVertex3f(-70.0f, y, -70.0f);
		glVertex3f(70.0f, y, -70.0f);
		glVertex3f(70.0f, y, 70.0f);
		glEnd();
		glPopMatrix();
	}
	void update(float fTimeElapsed)
	{
		if (stop) return;
		y -= 50.0f * fTimeElapsed;
		rad += 50.0f * fTimeElapsed;
		if (10.0f + num * 60.0f > y) stop = true;
	}
};

class CPractice23 : public CPractice
{
private:
	CCamera m_camera;
	CCube m_cube;
	CCube m_column;
	std::list<torus*> m_tList;
	std::list<surface*> m_sList;

	int order = 0;
	int sorder = 0;

	float m_tr = 0.0f;

	float m_angle_x = 0.0f;
	float m_angle_y = 0.0f;
	float m_angle_z = 0.0f;

	bool m_rotate_x = false;
	bool m_rotate_y = false;
	bool m_rotate_z = false;

	bool m_start = false;
	bool m_cull = false;
	bool m_depth = false;

public:
	CPractice23();
	~CPractice23();

	void DrawAxis();

	void Reset();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag);
	virtual void Rendering();
	virtual void Update(float fTimeElapsed);
	virtual bool ProcessInput();
};