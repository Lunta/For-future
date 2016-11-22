#include "stdafx.h"

#include "MainScene.h"
#include "Practice26.h"



CPractice26::CPractice26()
{
	m_cube.SetColor(128, 128, 128, 255);
	m_build_cone.SetColor(255, 0, 0, 255);
	m_tree_cube.SetColor(255, 255, 0, 255);
	m_tree_sphere.SetColor(255, 0, 255, 255);
	m_build_n.SetColor(0, 255, 255, 255);
	m_build_torus.SetColor(0, 0, 255, 255);
}


CPractice26::~CPractice26()
{
}
void CPractice26::DrawAxis()
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

void CPractice26::Reset()
{
	m_angle_x = 0.0f;
	m_angle_y = 0.0f;
	m_angle_z = 0.0f;

	m_rotate_x = false;
	m_rotate_y = false;
	m_rotate_z = false;
}

bool CPractice26::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice26::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
		m_pCamera->RotateViewDirection(LOWORD(lParam),HIWORD(lParam));
		break;
	}
	return false;
}

bool CPractice26::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice26::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
	m_cube.Scale(800.0f, 5.0f, 800.0f);
	m_cube.Translate(0.0f, -50.0f, 0.0f);
	m_build_cone.Scale(100.0f, 100.0f, 100.0f);
	m_build_cone.Translate(-200.0f, 50.0f, 200.0f);
	m_tree_cube.Scale(100.0f, 100.0f, 100.0f);
	m_tree_cube.Translate(200.0f, 0.0f, 200.0f);
	m_tree_sphere.Scale(100.0f, 100.0f, 100.0f);
	m_tree_sphere.Translate(200.0f, 0.0f, -200.0f);
	m_build_n.Scale(100.0f, 100.0f, 100.0f);
	m_build_n.Translate(0.0f, 0.0f, 0.0f);
	m_build_torus.Scale(100.0f, 100.0f, 100.0f);
	m_build_torus.Translate(-200.0f, 0.0f, -200.0f);
	m_pCamera = m_pScene->GetCamera();
}

void CPractice26::Rendering()
{
	glPushMatrix();
	glLoadIdentity();
	m_pCamera->LookAt();
	glRotatef(m_angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angle_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_angle_z, 0.0f, 0.0f, 1.0f);
	m_cube.Rendering();
	m_build_cone.Rendering();
	m_tree_cube.Rendering();
	m_tree_sphere.Rendering();
	m_build_n.Rendering();
	m_build_torus.Rendering();
	DrawAxis();
	glPopMatrix();
}

void CPractice26::Update(float fTimeElapsed)
{
	m_pCamera->Update(fTimeElapsed);
	ProcessInput();
	if (m_rotate_x) m_angle_x += 0.1f;
	if (m_rotate_y) m_angle_y += 0.1f;
	if (m_rotate_z) m_angle_z += 0.1f;
	m_build_cone.Update(fTimeElapsed);
	m_tree_cube.Update(fTimeElapsed);
	m_tree_sphere.Update(fTimeElapsed);
	m_build_n.Update(fTimeElapsed);
	m_build_torus.Update(fTimeElapsed);
}

bool CPractice26::ProcessInput()
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

			if (pKeyBuffer['X'] & 0xF0) { bControll = true; m_rotate_x = true; }
			if (pKeyBuffer['Y'] & 0xF0) { bControll = true; m_rotate_y = true; }
			if (pKeyBuffer['Z'] & 0xF0) { bControll = true; m_rotate_z = true; }
			if (pKeyBuffer['W'] & 0xF0) { bControll = true; m_pCamera->TranslatePos(0.0f, 0.0f, 0.1f); }
			if (pKeyBuffer['S'] & 0xF0) { bControll = true; m_pCamera->TranslatePos(0.0f, 0.0f, -0.1f);  }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['M'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_27); }
			else if (pKeyBuffer['V'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_25); }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true; m_pCamera->TranslatePos(0.1f, 0.0f, 0.0f);}
				if (dwDirection & DIR_RIGHT) { bControll = true; m_pCamera->TranslatePos(-0.1f, 0.0f, 0.0f);}
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true;  m_pCamera->TranslatePos(0.0f, 0.1f, 0.0f); }
				if (dwDirection & DIR_DOWN) { bControll = true; m_pCamera->TranslatePos(0.0f, -0.1f, 0.0f); }
			}
		}

		if (!bControll)
		{
			m_rotate_x = false;
			m_rotate_y = false;
			m_rotate_z = false;
		}
		return bControll;
	}
	return false;
}
