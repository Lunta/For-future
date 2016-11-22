#include "stdafx.h"

#include "MainScene.h"
#include "Practice15.h"


CPractice15::CPractice15()
{
}
CPractice15::~CPractice15()
{
}

void CPractice15::RotateAxis()
{
	glRotatef(m_rad_X, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rad_Y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rad_Z, 0.0f, 0.0f, 1.0f);
}

void CPractice15::DrawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void CPractice15::Reset()
{
	m_camera_X = 0.0f;
	m_camera_Y = 0.0f;
	m_camera_Z = 0.0f;

	m_rad_X = 0.0f;
	m_rad_Y = 0.0f;
	m_rad_Z = 0.0f;

	m_bRotate_X = false;
	m_bRotate_Y = false;
	m_bRotate_Z = false;
}

bool CPractice15::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice15::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice15::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice15::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
}
void CPractice15::Rendering()
{
	gluLookAt(m_camera_X, m_camera_Y, m_camera_Z, m_camera_X, m_camera_Y, m_camera_Z + 100.0f, 0.0f, 1.0f, 0.0f);
	RotateAxis();
	DrawAxis();
	glColor3f(1.0f, 1.0f, 0.0f);
	m_orbit.Rendering(100.0f);
}

void CPractice15::Update(float fTimeElapsed)
{
	ProcessInput();
	m_orbit.Update(fTimeElapsed);
	if (m_bRotate_X) m_rad_X += 0.1f;
	if (m_bRotate_Y) m_rad_Y += 0.1f;
	if (m_bRotate_Z) m_rad_Z += 0.1f;
}

bool CPractice15::ProcessInput()
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

			if (pKeyBuffer['X'] & 0xF0) { bControll = true; m_bRotate_X = true; }
			else if (pKeyBuffer['Y'] & 0xF0) { bControll = true; m_bRotate_Y = true; }
			else if (pKeyBuffer['Z'] & 0xF0) { bControll = true; m_bRotate_Z = true; }
			else if (pKeyBuffer['W'] & 0xF0) { bControll = true; m_camera_Z++; }
			else if (pKeyBuffer['S'] & 0xF0) { bControll = true; m_camera_Z--;}
			else if (pKeyBuffer['C'] & 0xF0) { bControll = true; m_orbit.SwapType(); }
			else if (pKeyBuffer['I'] & 0xF0) { bControll = true; Reset(); }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['V'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_14); }
			else if (pKeyBuffer['M'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_16); }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true;  m_camera_X += 1.0f; }
				if (dwDirection & DIR_RIGHT) { bControll = true; m_camera_X -= 1.0f;}
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true;  m_camera_Y += 1.0f; }
				if (dwDirection & DIR_DOWN) { bControll = true; m_camera_Y -= 1.0f; }
			}
		}

		if (!bControll)
		{
			m_bRotate_X = false;
			m_bRotate_Y = false;
			m_bRotate_Z = false;
		}

		return bControll;
	}
	return false;
}
