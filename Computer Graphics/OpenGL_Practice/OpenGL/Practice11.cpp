#include "stdafx.h"

#include "MainScene.h"
#include "Practice11.h"


CPractice11::CPractice11()
{
}


CPractice11::~CPractice11()
{
}

void CPractice11::DrawAxis()
{
	glColor3f(1.0f, 1.0f, 1.0f); // 빨강색
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
}

void CPractice11::DrawSin()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.6f, 0.0f);
	glRotatef(m_fRotateAngle_X, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotateAngle_Y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fRotateAngle_Z, 0.0f, 0.0f, 1.0f);
	glTranslatef(m_fTranslateLength, 0.0f, 0.0f);
	glScalef(m_fScale, m_fScale, m_fScale);
	glBegin(GL_LINES);
	for (int i = 0; i < 500; i++)
	{
		glColor3f(1.0f - 0.002f * i, 0, 0.002f * i);
		glVertex3f(0.002f * i - 0.5f, m_fScale * 0.1f * sinf(0.1f * i + m_fStartAngle), 0.0f);
		glVertex3f(0.002f * (i + 1) - 0.5f, m_fScale * 0.1f*sinf(0.1f * (i + 1) + m_fStartAngle), 0.0f);
	}
	glEnd();
	glPopMatrix();
}

void CPractice11::DrawCos()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glRotatef(m_fRotateAngle_X, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotateAngle_Y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fRotateAngle_Z, 0.0f, 0.0f, 1.0f);
	glTranslatef(m_fTranslateLength, 0.0f, 0.0f);
	glScalef(m_fScale, m_fScale, m_fScale);
	glBegin(GL_LINES);
	for (int i = 0; i < 500; i++)
	{
		glColor3f(1.0f - 0.002f * i, 0, 0.002f * i);
		glVertex3f(0.002f * i - 0.5f, 0.1f * cosf(0.1f * i + m_fStartAngle), 0.0f);
		glVertex3f(0.002f * (i + 1) - 0.5f, 0.1f*cosf(0.1f * (i + 1) + m_fStartAngle), 0.0f);
	}
	glEnd();
	glPopMatrix();
}

void CPractice11::DrawSpring()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, -0.2f, 0.0f);
	glRotatef(m_fRotateAngle_X, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotateAngle_Y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fRotateAngle_Z, 0.0f, 0.0f, 1.0f);
	glTranslatef(m_fTranslateLength, 0.0f, 0.0f);
	glScalef(m_fScale, m_fScale, m_fScale);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 500; i++)
	{
		glColor3f(1.0f - 0.002f * i, 0, 0.002f * i);
		glVertex3f(0.1f * cosf(0.1f * i + m_fStartAngle) + 0.002f * i - 0.5f, 0.1f * sinf(0.1f * i + m_fStartAngle), 0.0f);
		glVertex3f(0.1f * cosf(0.1f * (i + 1) + m_fStartAngle) + 0.002f * (i + 1) - 0.5f, 0.1f * sinf(0.1f * (i + 1) + m_fStartAngle), 0.0f);
	}
	glEnd();
	glPopMatrix();
}

void CPractice11::DrawRect()
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, -0.6f, 0.0f);
	glRotatef(m_fRotateAngle_X, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotateAngle_Y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fRotateAngle_Z, 0.0f, 0.0f, 1.0f);
	glTranslatef(m_fTranslateLength, 0.0f, 0.0f);
	glScalef(m_fScale, m_fScale, m_fScale);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-0.5, 0.0, 0.0);
	for (int i = 0; i < 11; i++)
	{
		glutSolidCube(0.05);
		glTranslatef(0.1, 0.0, 0.0);
	}
	glPopMatrix();
}

bool CPractice11::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice11::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice11::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice11::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
}

void CPractice11::Rendering()
{
	// 축 그리기
	DrawAxis();
	// 사인곡선
	DrawSin();
	// 코사인곡선
	DrawCos();
	// 스프링 곡선
	DrawSpring();
	// 직사각형
	DrawRect();
	
}

void CPractice11::Update(float fTimeElapsed)
{
	ProcessInput();
	if (m_bReset)
	{
		m_fStartAngle = 0.0f;
		m_fScale = 1.0f;
		m_fRotateAngle_X = 0.0f;
		m_fRotateAngle_Y = 0.0f;
		m_fRotateAngle_Z = 0.0f;
		m_fTranslateLength = 0.0f;
	}
	if (m_bAnimation) m_fStartAngle += 0.01f;
	if (m_bScale) m_fScale += 0.01f;
	if (m_bDeScale) m_fScale -= 0.01f;
	if (m_bRotate_Axis_X) m_fRotateAngle_X += 0.05f;
	if (m_bRotate_Axis_Y) m_fRotateAngle_Y += 0.05f;
	if (m_bRotate_Axis_Z) m_fRotateAngle_Z += 0.05f;
	if (m_bTranslate_Left) m_fTranslateLength -= 0.003f;
	if (m_bTranslate_Right) m_fTranslateLength += 0.003f;
}

bool CPractice11::ProcessInput()
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

			if (pKeyBuffer['X'] & 0xF0) { bControll = true; m_bRotate_Axis_X = true; }
			else if (pKeyBuffer['Y'] & 0xF0) { bControll = true; m_bRotate_Axis_Y = true; }
			else if (pKeyBuffer['Z'] & 0xF0) { bControll = true; m_bRotate_Axis_Z = true; }
			else if (pKeyBuffer['S'] & 0xF0) { bControll = true; m_bScale = true; }
			else if (pKeyBuffer['D'] & 0xF0) { bControll = true; m_bDeScale = true; }
			else if (pKeyBuffer['A'] & 0xF0) { bControll = true; m_bAnimation = true; }
			else if (pKeyBuffer['I'] & 0xF0) { bControll = true; m_bReset = true; }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['N'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_12); }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true; m_bTranslate_Left = true; }
				if (dwDirection & DIR_RIGHT) { bControll = true; m_bTranslate_Right = true; }
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true; }
				if (dwDirection & DIR_DOWN) { bControll = true; }
			}
		}

		if (!bControll)
		{
			m_bRotate_Axis_X = false;
			m_bRotate_Axis_Y = false;
			m_bRotate_Axis_Z = false;
			m_bReset = false;
			m_bAnimation = false;
			m_bScale = false;
			m_bDeScale = false;
			m_bTranslate_Left = false;
			m_bTranslate_Right = false;
		}

		return bControll;
	}
	return false;
}
