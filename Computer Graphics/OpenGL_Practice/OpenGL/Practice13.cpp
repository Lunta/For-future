#include "stdafx.h"

#include "MainScene.h"
#include "Practice13.h"


CPractice13::CPractice13()
{
	m_x = 0.0f;
	m_y = 0.4f;
	m_rad = 0.0f;
}
CPractice13::~CPractice13()
{
}

void CPractice13::DrawAixs()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();
}

void CPractice13::DrawTriangles()
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glVertex3f(-0.3f, -0.2f, 0.0f);
	glVertex3f(0.3f, -0.2f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glVertex3f(0.0f, -0.2f, -0.3f);
	glVertex3f(0.0f, -0.2f, 0.3f);
	glEnd();
}

void CPractice13::DrawRotateTriangles()
{
	glPushMatrix();
	glTranslatef(m_x, m_y, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(-0.05f, -0.05f, 0.0f);
	glVertex3f(0.05f, -0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, m_y, m_x);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, -0.05f, -0.05f);
	glVertex3f(0.0f, -0.05f, 0.05f);
	glEnd();
	glPopMatrix();
}

bool CPractice13::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	}
	return false;
}

bool CPractice13::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return false;
}

bool CPractice13::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:
		break;
	case WM_DESTROY:
		break;
	}
	return false;
}

void CPractice13::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
}

void CPractice13::Rendering()
{
	DrawAixs();
	if (m_bRotate)
	{
		glRotatef(m_rad, 0.0f, 1.0f, 0.0f);
	}
	DrawTriangles();
	DrawRotateTriangles();
}

void CPractice13::Update(float fTimeElapsed)
{
	ProcessInput();
	if (m_bRotate)m_rad += 0.01f;
	if (m_bUp)
		m_x += 0.0002f;
	else
	{
		m_x -= 0.0002f;
		if(m_x < 0.0f) m_y -= 0.0004f;
		else if (m_x > 0.0f) m_y += 0.0004f;
	}
	if (m_x < -0.3f) m_bUp = true;
	else if (m_x > 0.3f) m_bUp = false;
}

bool CPractice13::ProcessInput()
{
	bool bProcessedByScene = false;

	if (!bProcessedByScene)
	{
		static UCHAR pKeyBuffer[256];
		DWORD dwDirection = 0;

		bool bPushShift = false;
		bool bControll = false;

		if (GetKeyboardState(pKeyBuffer))
		{
			if (pKeyBuffer[VK_LSHIFT] & 0xF0)	  bPushShift = true;
			if (pKeyBuffer[VK_LEFT] & 0xF0)  	  dwDirection |= DIR_LEFT;
			if (pKeyBuffer[VK_RIGHT] & 0xF0)	  dwDirection |= DIR_RIGHT;
			if (pKeyBuffer[VK_UP] & 0xF0)		  dwDirection |= DIR_UP;
			if (pKeyBuffer[VK_DOWN] & 0xF0)		  dwDirection |= DIR_DOWN;

			if (pKeyBuffer['R'] & 0xF0) { bControll = true;  if (m_bRotate) m_bRotate = false; else m_bRotate = true; }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['B'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_12); }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true; }
				if (dwDirection & DIR_RIGHT) { bControll = true; }
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true; }
				if (dwDirection & DIR_DOWN) { bControll = true; }
			}
		}

		if (!bControll)
		{

		}

		return bControll;
	}
	return false;
}
