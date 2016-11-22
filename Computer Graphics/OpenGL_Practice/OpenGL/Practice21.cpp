#include "stdafx.h"

#include "MainScene.h"
#include "Practice21.h"


CPractice21::CPractice21()
{
	m_angle_x = 30.0f;
	m_angle_y = 45.0f;
	m_uprotate = 0.0f;
	m_forwardrotate = 0.0f;
	m_Cube[CubePos::LTF] = { -1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::LTB] = { -1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::RTF] = {  1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::RTB] = {  1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::LBF] = { -1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::LBB] = { -1.0f, -1.0f, -1.0f };
	m_Cube[CubePos::RBF] = {  1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::RBB] = {  1.0f, -1.0f, -1.0f };
	m_scale = { 1.0f,  1.0f,  1.0f };
	m_shade = false;
	m_culling = false;
	m_depth = false;
	m_upsurface = false;
	m_forwardsurface = false;
}
CPractice21::~CPractice21()
{
}

void CPractice21::DrawAxis()
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

void CPractice21::DrawCube()
{
	// À­¸é
	glPushMatrix();
	glTranslatef(1.0f, 1.0f, 0.0f);
	glRotated(-m_uprotate, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.0f, -1.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::RTF].color.red, m_Cube[CubePos::RTF].color.green, m_Cube[CubePos::RTF].color.blue, m_Cube[CubePos::RTF].color.alpha);
	glVertex3f(m_Cube[CubePos::RTF].x, m_Cube[CubePos::RTF].y, m_Cube[CubePos::RTF].z);
	glColor4f(m_Cube[CubePos::RTB].color.red, m_Cube[CubePos::RTB].color.green, m_Cube[CubePos::RTB].color.blue, m_Cube[CubePos::RTB].color.alpha);
	glVertex3f(m_Cube[CubePos::RTB].x, m_Cube[CubePos::RTB].y, m_Cube[CubePos::RTB].z);
	glColor4f(m_Cube[CubePos::LTB].color.red, m_Cube[CubePos::LTB].color.green, m_Cube[CubePos::LTB].color.blue, m_Cube[CubePos::LTB].color.alpha);
	glVertex3f(m_Cube[CubePos::LTB].x, m_Cube[CubePos::LTB].y, m_Cube[CubePos::LTB].z);
	glColor4f(m_Cube[CubePos::LTF].color.red, m_Cube[CubePos::LTF].color.green, m_Cube[CubePos::LTF].color.blue, m_Cube[CubePos::LTF].color.alpha);
	glVertex3f(m_Cube[CubePos::LTF].x, m_Cube[CubePos::LTF].y, m_Cube[CubePos::LTF].z);
	glEnd();
	glPopMatrix();
	// ¿À¸¥ÂÊ¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::RTF].color.red, m_Cube[CubePos::RTF].color.green, m_Cube[CubePos::RTF].color.blue, m_Cube[CubePos::RTF].color.alpha);
	glVertex3f(m_Cube[CubePos::RTF].x, m_Cube[CubePos::RTF].y, m_Cube[CubePos::RTF].z);
	glColor4f(m_Cube[CubePos::RTB].color.red, m_Cube[CubePos::RTB].color.green, m_Cube[CubePos::RTB].color.blue, m_Cube[CubePos::RTB].color.alpha);
	glVertex3f(m_Cube[CubePos::RTB].x, m_Cube[CubePos::RTB].y, m_Cube[CubePos::RTB].z);
	glColor4f(m_Cube[CubePos::RBB].color.red, m_Cube[CubePos::RBB].color.green, m_Cube[CubePos::RBB].color.blue, m_Cube[CubePos::RBB].color.alpha);
	glVertex3f(m_Cube[CubePos::RBB].x, m_Cube[CubePos::RBB].y, m_Cube[CubePos::RBB].z);
	glColor4f(m_Cube[CubePos::RBF].color.red, m_Cube[CubePos::RBF].color.green, m_Cube[CubePos::RBF].color.blue, m_Cube[CubePos::RBF].color.alpha);
	glVertex3f(m_Cube[CubePos::RBF].x, m_Cube[CubePos::RBF].y, m_Cube[CubePos::RBF].z);
	glEnd();
	// ¿ÞÂÊ¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::LTB].color.red, m_Cube[CubePos::LTB].color.green, m_Cube[CubePos::LTB].color.blue, m_Cube[CubePos::LTB].color.alpha);
	glVertex3f(m_Cube[CubePos::LTB].x, m_Cube[CubePos::LTB].y, m_Cube[CubePos::LTB].z);
	glColor4f(m_Cube[CubePos::LTF].color.red, m_Cube[CubePos::LTF].color.green, m_Cube[CubePos::LTF].color.blue, m_Cube[CubePos::LTF].color.alpha);
	glVertex3f(m_Cube[CubePos::LTF].x, m_Cube[CubePos::LTF].y, m_Cube[CubePos::LTF].z);
	glColor4f(m_Cube[CubePos::LBF].color.red, m_Cube[CubePos::LBF].color.green, m_Cube[CubePos::LBF].color.blue, m_Cube[CubePos::LBF].color.alpha);
	glVertex3f(m_Cube[CubePos::LBF].x, m_Cube[CubePos::LBF].y, m_Cube[CubePos::LBF].z);
	glColor4f(m_Cube[CubePos::LBB].color.red, m_Cube[CubePos::LBB].color.green, m_Cube[CubePos::LBB].color.blue, m_Cube[CubePos::LBB].color.alpha);
	glVertex3f(m_Cube[CubePos::LBB].x, m_Cube[CubePos::LBB].y, m_Cube[CubePos::LBB].z);
	glEnd();
	// ¾Õ¸é
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 1.0f);
	glRotated(-m_forwardrotate, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -1.0f, -1.0f);
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::RTF].color.red, m_Cube[CubePos::RTF].color.green, m_Cube[CubePos::RTF].color.blue, m_Cube[CubePos::RTF].color.alpha);
	glVertex3f(m_Cube[CubePos::RTF].x, m_Cube[CubePos::RTF].y, m_Cube[CubePos::RTF].z);
	glColor4f(m_Cube[CubePos::LTF].color.red, m_Cube[CubePos::LTF].color.green, m_Cube[CubePos::LTF].color.blue, m_Cube[CubePos::LTF].color.alpha);
	glVertex3f(m_Cube[CubePos::LTF].x, m_Cube[CubePos::LTF].y, m_Cube[CubePos::LTF].z);
	glColor4f(m_Cube[CubePos::LBF].color.red, m_Cube[CubePos::LBF].color.green, m_Cube[CubePos::LBF].color.blue, m_Cube[CubePos::LBF].color.alpha);
	glVertex3f(m_Cube[CubePos::LBF].x, m_Cube[CubePos::LBF].y, m_Cube[CubePos::LBF].z);
	glColor4f(m_Cube[CubePos::RBF].color.red, m_Cube[CubePos::RBF].color.green, m_Cube[CubePos::RBF].color.blue, m_Cube[CubePos::RBF].color.alpha);
	glVertex3f(m_Cube[CubePos::RBF].x, m_Cube[CubePos::RBF].y, m_Cube[CubePos::RBF].z);
	glEnd();
	glPopMatrix();
	// µÞ¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::RTB].color.red, m_Cube[CubePos::RTB].color.green, m_Cube[CubePos::RTB].color.blue, m_Cube[CubePos::RTB].color.alpha);
	glVertex3f(m_Cube[CubePos::RTB].x, m_Cube[CubePos::RTB].y, m_Cube[CubePos::RTB].z);
	glColor4f(m_Cube[CubePos::LTB].color.red, m_Cube[CubePos::LTB].color.green, m_Cube[CubePos::LTB].color.blue, m_Cube[CubePos::LTB].color.alpha);
	glVertex3f(m_Cube[CubePos::LTB].x, m_Cube[CubePos::LTB].y, m_Cube[CubePos::LTB].z);
	glColor4f(m_Cube[CubePos::LBB].color.red, m_Cube[CubePos::LBB].color.green, m_Cube[CubePos::LBB].color.blue, m_Cube[CubePos::LBB].color.alpha);
	glVertex3f(m_Cube[CubePos::LBB].x, m_Cube[CubePos::LBB].y, m_Cube[CubePos::LBB].z);
	glColor4f(m_Cube[CubePos::RBB].color.red, m_Cube[CubePos::RBB].color.green, m_Cube[CubePos::RBB].color.blue, m_Cube[CubePos::RBB].color.alpha);
	glVertex3f(m_Cube[CubePos::RBB].x, m_Cube[CubePos::RBB].y, m_Cube[CubePos::RBB].z);
	glEnd();
	// ¾Æ·§¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::LBF].color.red, m_Cube[CubePos::LBF].color.green, m_Cube[CubePos::LBF].color.blue, m_Cube[CubePos::LBF].color.alpha);
	glVertex3f(m_Cube[CubePos::LBF].x, m_Cube[CubePos::LBF].y, m_Cube[CubePos::LBF].z);
	glColor4f(m_Cube[CubePos::LBB].color.red, m_Cube[CubePos::LBB].color.green, m_Cube[CubePos::LBB].color.blue, m_Cube[CubePos::LBB].color.alpha);
	glVertex3f(m_Cube[CubePos::LBB].x, m_Cube[CubePos::LBB].y, m_Cube[CubePos::LBB].z);
	glColor4f(m_Cube[CubePos::RBB].color.red, m_Cube[CubePos::RBB].color.green, m_Cube[CubePos::RBB].color.blue, m_Cube[CubePos::RBB].color.alpha);
	glVertex3f(m_Cube[CubePos::RBB].x, m_Cube[CubePos::RBB].y, m_Cube[CubePos::RBB].z);
	glColor4f(m_Cube[CubePos::RBF].color.red, m_Cube[CubePos::RBF].color.green, m_Cube[CubePos::RBF].color.blue, m_Cube[CubePos::RBF].color.alpha);
	glVertex3f(m_Cube[CubePos::RBF].x, m_Cube[CubePos::RBF].y, m_Cube[CubePos::RBF].z);
	glEnd();
}

void CPractice21::Reset()
{
	m_angle_x = 30.0f;
	m_angle_y = 45.0f;
	m_angle_z = 0.0f;

	m_rotate_x = false;
	m_rotate_y = false;
	m_rotate_z = false;
}

bool CPractice21::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice21::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice21::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice21::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
	m_Cube[CubePos::LTF].SetColor(255, 255, 0);
	m_Cube[CubePos::LTB].SetColor(255, 255, 255);
	m_Cube[CubePos::RTF].SetColor(0, 255, 0);
	m_Cube[CubePos::RTB].SetColor(0, 255, 255);
	m_Cube[CubePos::LBF].SetColor(255, 0, 0);
	m_Cube[CubePos::LBB].SetColor(255, 0, 255);
	m_Cube[CubePos::RBF].SetColor(0, 0, 0);
	m_Cube[CubePos::RBB].SetColor(0, 0, 255);
	m_scale = { 70.0f, 70.0f, 70.0f };
	
}

void CPractice21::Rendering()
{
	if (m_depth) glDisable(GL_DEPTH_TEST);
	else glEnable(GL_DEPTH_TEST);
	if (m_culling) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
	if (m_shade) glShadeModel(GL_FLAT);
	else glShadeModel(GL_SMOOTH);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(m_camera.pos.x, m_camera.pos.y, m_camera.pos.z,
		m_camera.pos.x + m_camera.look.x, m_camera.pos.y + m_camera.look.y, m_camera.pos.z + m_camera.look.z,
		m_camera.up.x, m_camera.up.y, m_camera.up.z);
	glRotatef(m_angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angle_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_angle_z, 0.0f, 0.0f, 1.0f);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	DrawCube();
	DrawAxis();
	glPopMatrix();
}

void CPractice21::Update(float fTimeElapsed)
{
	ProcessInput();
	if (m_rotate_x) m_angle_x += 0.1f;
	if (m_rotate_y) m_angle_y += 10.0f * fTimeElapsed;
	m_angle_y += 10.0f * fTimeElapsed;
	if (m_rotate_z) m_angle_z += 0.1f;

	if (m_upsurface && m_uprotate < 90.0f)
		m_uprotate += 30.0f * fTimeElapsed;
	if (m_forwardsurface && m_forwardrotate < 90.0f) m_forwardrotate += 30.0f * fTimeElapsed;
}

bool CPractice21::ProcessInput()
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
			if (pKeyBuffer[VK_NUMPAD1] & 0xF0) { bControll = true; m_depth = true; }
			if (pKeyBuffer[VK_NUMPAD2] & 0xF0) { bControll = true; m_culling = true; }
			if (pKeyBuffer[VK_NUMPAD3] & 0xF0) { bControll = true; m_shade = true;	}
			if (pKeyBuffer['R'] & 0xF0) { bControll = true; m_upsurface = true; }
			if (pKeyBuffer['T'] & 0xF0) { bControll = true; m_upsurface = false; m_uprotate = 0.0f; }
			if (pKeyBuffer['F'] & 0xF0) { bControll = true; m_forwardsurface = true; }
			if (pKeyBuffer['G'] & 0xF0) { bControll = true; m_forwardsurface = false; m_forwardrotate = 0.0f; }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['M'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_22); }
			else if (pKeyBuffer['V'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_20); }
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

			m_shade = false;
			m_culling = false;
			m_depth = false;
			
		}

		return bControll;
	}
	return false;
}
