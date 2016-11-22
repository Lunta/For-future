#include "stdafx.h"

#include "MainScene.h"
#include "Practice18.h"


CPractice18::CPractice18()
{
	m_sphere.SetColor(255, 0, 255, 255);
	m_cube.SetColor(128, 128, 128, 255);
}
CPractice18::~CPractice18()
{
}

void CPractice18::DrawAxis()
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

void CPractice18::Reset()
{
	m_Crane.Reset();
	m_sphere.Reset();
	m_angle_x = 0.0f;
	m_angle_y = 0.0f;
	m_angle_z = 0.0f;

	m_rotate_x = false;
	m_rotate_y = false;
	m_rotate_z = false;

	m_collide = false;
	m_collide_Timer = 0.0f;
}

bool CPractice18::CheckCollide(Vertex3f * a, Vertex3f * b)
{
	if (a[ForwardLeftTop].z < b[BackLeftTop].z) return false;
	if (a[BackLeftTop].z > b[ForwardLeftTop].z) return false;
	if (a[ForwardLeftTop].x > b[ForwardRightTop].x) return false;
	if (a[ForwardRightTop].x < b[ForwardLeftTop].x) return false;
	if (a[ForwardLeftTop].y < b[ForwardLeftDown].y) return false;
	if (a[ForwardLeftDown].y > b[ForwardLeftTop].y) return false;
	return true;
}

bool CPractice18::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice18::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice18::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice18::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
	m_Crane.Scale(100.0f, 100.0f, 100.0f);
	m_Crane.Translate(0.0f, -30.0f, -100.0f);
	m_cube.Scale(400.0f, 5.0f, 400.0f);
	m_cube.Translate(0.0f, -50.0f, 0.0f);
	m_sphere.SetField(200.0f);
	m_sphere.Scale(20.0f, 20.0f, 20.0f);
	m_sphere.Translate(0.0f, -40.0f, 0.0f);
}

void CPractice18::Rendering()
{
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(m_camera.pos.x, m_camera.pos.y, m_camera.pos.z,
		m_camera.pos.x + m_camera.look.x, m_camera.pos.y + m_camera.look.y, m_camera.pos.z + m_camera.look.z,
		m_camera.up.x, m_camera.up.y, m_camera.up.z);
	glRotatef(m_angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angle_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_angle_z, 0.0f, 0.0f, 1.0f);
	m_cube.Rendering();
	m_Crane.Rendering(true);
	m_sphere.Rendering();
	DrawAxis();
	glPopMatrix();
}

void CPractice18::Update(float fTimeElapsed)
{
	ProcessInput();
	if (m_rotate_x) m_angle_x += 0.1f;
	if (m_rotate_y) m_angle_y += 0.1f;
	if (m_rotate_z) m_angle_z += 0.1f;
	m_Crane.Update(fTimeElapsed);
	if (CheckCollide(m_sphere.GetBB(), m_Crane.GetBB()))
	{
		Vec3f temp = (m_sphere.GetCenter() -m_Crane.GetCenter());
		temp.Normalize();
		m_sphere.Translate(temp.x * 0.01f, 0.0f, temp.z * 0.01f);
		m_Crane.Stop();
		m_collide = true;
	}
	if (m_collide) m_collide_Timer += fTimeElapsed;
	if (m_collide_Timer > 0.5)
	{
		m_collide = false;
		m_Crane.Stop(false);
		m_collide_Timer = 0.0f;
	}
}

bool CPractice18::ProcessInput()
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
			if (pKeyBuffer['W'] & 0xF0) { bControll = true; m_camera.pos.z += 1; }
			if (pKeyBuffer['S'] & 0xF0) { bControll = true; m_camera.pos.z -= 1; }
			if (pKeyBuffer['R'] & 0xF0) { bControll = true; m_sphere.move(0.05f, true, false, false);}
			if (pKeyBuffer['F'] & 0xF0) { bControll = true; m_sphere.move(-0.05f, true, false, false); }
			if (pKeyBuffer['D'] & 0xF0) { bControll = true; m_sphere.move(-0.05f, false, false, true); }
			if (pKeyBuffer['G'] & 0xF0) { bControll = true; m_sphere.move(0.05f, false, false, true); }
			if (pKeyBuffer['I'] & 0xF0) { bControll = true; Reset(); }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['N'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_19); }
			else if (pKeyBuffer['B'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_17); }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true; m_camera.pos.x += 1.0f; }
				if (dwDirection & DIR_RIGHT) { bControll = true; m_camera.pos.x -= 1.0f; }
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true;  m_camera.pos.y += 1.0f; }
				if (dwDirection & DIR_DOWN) { bControll = true; m_camera.pos.y -= 1.0f; }
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
