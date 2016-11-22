#include "stdafx.h"

#include "MainScene.h"
#include "Practice14.h"


CPractice14::CPractice14()
{
}
CPractice14::~CPractice14()
{
}

void CPractice14::DrawAxis()
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

void CPractice14::DrawFloor()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-300.0f, -100.0f, -300.0f);
	glVertex3f(300.0f, -100.0f, -300.0f);
	glVertex3f(300.0f, -100.0f, 300.0f);
	glVertex3f(-300.0f, -100.0f, 300.0f);
	glEnd();
}

void CPractice14::DrawFigure_Solid()
{
	glColor3f(0.5f, 0.5f, 0.5f);
	switch (m_type)
	{
	case Figure::Cone:
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(50.0f, 100.0f, 10, 10);
		break;
	case Figure::Teapot:
		glutSolidTeapot(50.0f);
		break;
	case Figure::Cube:
		glutSolidCube(50.0f);
		break;
	case Figure::Sphere:
		glutSolidSphere(50.0f, 10, 10);
		break;
	}
	
}

void CPractice14::DrawFigure_Wire()
{
	glColor3f(0.0f, 1.0f, 1.0f);
	switch (m_type)
	{
	case Figure::Cone:
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutWireCone(50.0f, 100.0f, 10, 10);
		break;
	case Figure::Teapot:
		glutWireTeapot(50.0f);
		break;
	case Figure::Cube:
		glutWireCube(50.0f);
		break;
	case Figure::Sphere:
		glutWireSphere(50.0f, 10, 10);
		break;
	}
}

void CPractice14::RotateAxis()
{
	glRotatef(m_rad_X, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rad_Y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rad_Z, 0.0f, 0.0f, 1.0f);
}

void CPractice14::Reset()
{
	m_camera_Z = 0.0f;

	m_rad_X = 0.0f;
	m_rad_Y = 0.0f;
	m_rad_Z = 0.0f;

	m_rad_Solid = 0.0f;
	m_rad_Wire = 0.0f;

	m_bRotate_Wire = false;
	m_bRotate_Solid = false;
	m_bRotate_X = false;
	m_bRotate_Y = false;
	m_bRotate_Z = false;
}

bool CPractice14::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice14::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice14::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice14::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
}

void CPractice14::Rendering()
{
	gluLookAt(0.0f, 0.0f, m_camera_Z, 0.0f, 0.0f, m_camera_Z + 100.0f , 0.0f, 1.0f, 0.0f);

	RotateAxis();
	DrawFloor();

	glPushMatrix();
	glTranslatef(-100.0f, -100.0f, 0.0f);
	glRotatef(m_rad_Solid, 0.0f, 1.0f, 0.0f);
	DrawFigure_Solid();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(100.0f, -100.0f, 0.0f);
	glRotatef(m_rad_Wire, 0.0f, 1.0f, 0.0f);
	DrawFigure_Wire();
	glPopMatrix();

	DrawAxis();
}

void CPractice14::Update(float fTimeElapsed)
{
	ProcessInput();
	if (m_bRotate_X) m_rad_X += 0.1f;
	if (m_bRotate_Y) m_rad_Y += 0.1f;
	if (m_bRotate_Z) m_rad_Z += 0.1f;
	if (m_bRotate_Solid) m_rad_Solid += 0.1f;
	if (m_bRotate_Wire) m_rad_Wire += 0.1f;
}

bool CPractice14::ProcessInput()
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

			if (pKeyBuffer[VK_NUMPAD0] & 0xF0) { bControll = true; m_type = Figure::Cube; }
			if (pKeyBuffer[VK_NUMPAD1] & 0xF0) { bControll = true; m_type = Figure::Cone; }
			if (pKeyBuffer[VK_NUMPAD2] & 0xF0) { bControll = true; m_type = Figure::Sphere; }
			if (pKeyBuffer[VK_NUMPAD3] & 0xF0) { bControll = true; m_type = Figure::Teapot; }
			if (pKeyBuffer['I'] & 0xF0) { bControll = true; Reset(); }
			else if (pKeyBuffer['R'] & 0xF0) { bControll = true; m_bRotate_Wire = true; }
			else if (pKeyBuffer['L'] & 0xF0) { bControll = true; m_bRotate_Solid = true;	}
			else if (pKeyBuffer['X'] & 0xF0) { bControll = true; m_bRotate_X = true; }
			else if (pKeyBuffer['Y'] & 0xF0) { bControll = true; m_bRotate_Y = true; }
			else if (pKeyBuffer['Z'] & 0xF0) { bControll = true; m_bRotate_Z = true; }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['N'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_15); }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true; }
				if (dwDirection & DIR_RIGHT) { bControll = true; }
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true; m_camera_Z++; }
				if (dwDirection & DIR_DOWN) { bControll = true; m_camera_Z--; }
			}
		}

		if (!bControll)
		{
			m_bRotate_Wire = false;
			m_bRotate_Solid	= false;
			m_bRotate_X	= false;
			m_bRotate_Y	= false;
			m_bRotate_Z	= false;
		}

		return bControll;
	}
	return false;
}
