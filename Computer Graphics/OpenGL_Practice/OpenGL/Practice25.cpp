#include "stdafx.h"

#include "MainScene.h"
#include "Practice25.h"


CPractice25::CPractice25()
{
	for (int i = 0; i < MAXIDX; i++)
	{
		ctrlpoints[i][0] = 0.0f;
		ctrlpoints[i][1] = 0.0f;
		ctrlpoints[i][2] = 0.0f;
	}
	idx = 0;
}
CPractice25::~CPractice25()
{
}

void CPractice25::DrawAxis()
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

void CPractice25::Reset()
{
	m_angle_x = 0.0f;
	m_angle_y = 0.0f;
	m_angle_z = 0.0f;

	m_rotate_x = false;
	m_rotate_y = false;
	m_rotate_z = false;

	for (int i = 0; i < MAXIDX; i++)
	{
		ctrlpoints[i][0] = 0.0f;
		ctrlpoints[i][1] = 0.0f;
		ctrlpoints[i][2] = 0.0f;
	}
	idx = 0;
}

bool CPractice25::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice25::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		if (idx < MAXIDX)
		{
			float w = CLIENT_WIDTH / 2.0f;
			float h = CLIENT_HEIGHT / 2.0f;
			for (int i = idx; i < MAXIDX; i++)
			{
				ctrlpoints[i][0] = -static_cast<float>((LOWORD(lParam) - w));
				ctrlpoints[i][1] = -static_cast<float>((HIWORD(lParam) - h));
				ctrlpoints[i][2] = 0.0f;
			}
			idx++;
		}
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

bool CPractice25::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice25::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
}

void CPractice25::Rendering()
{
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(m_camera.pos.x, m_camera.pos.y, m_camera.pos.z,
		m_camera.pos.x + m_camera.look.x, m_camera.pos.y + m_camera.look.y, m_camera.pos.z + m_camera.look.z,
		m_camera.up.x, m_camera.up.y, m_camera.up.z);
	glRotatef(m_angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angle_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_angle_z, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < MAXIDX / 3; i++)
	{
		glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, 4, &ctrlpoints[i * 3][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glMapGrid1f(100.0, 0, 1.0); // 매개변수 0~1 사이를 100개로 나눔
		glEvalMesh1(GL_LINE, 0, 100);
		glDisable(GL_MAP1_VERTEX_3);
	}
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < MAXIDX; i++)
		glVertex3fv(&ctrlpoints[i][0]);
	glEnd();

	DrawAxis();
	glPopMatrix();
}

void CPractice25::Update(float fTimeElapsed)
{
	ProcessInput();
	if (m_rotate_x) m_angle_x += 0.1f;
	if (m_rotate_y) m_angle_y += 0.1f;
	if (m_rotate_z) m_angle_z += 0.1f;
}

bool CPractice25::ProcessInput()
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
			if (pKeyBuffer['R'] & 0xF0) { bControll = true; Reset(); }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['M'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_26); }
			else if (pKeyBuffer['V'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_24); }
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
