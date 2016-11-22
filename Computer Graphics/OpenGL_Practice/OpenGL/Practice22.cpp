#include "stdafx.h"

#include "MainScene.h"
#include "Practice22.h"


CPractice22::CPractice22()
{
	m_Cube[CubePos::LTF] = { -1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::LTB] = { -1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::RTF] = { 1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::RTB] = { 1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::LBF] = { -1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::LBB] = { -1.0f, -1.0f, -1.0f };
	m_Cube[CubePos::RBF] = { 1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::RBB] = { 1.0f, -1.0f, -1.0f };
	m_scale = { 1.0f,  1.0f,  1.0f };
	m_Surface[SFormularf::Surface::Top].SetFormular(m_Cube[CubePos::RTF], m_Cube[CubePos::RTB], m_Cube[CubePos::LTB]);
	m_Surface[SFormularf::Surface::Bottom].SetFormular(m_Cube[CubePos::LBF], m_Cube[CubePos::LBB], m_Cube[CubePos::RBB]);
	m_Surface[SFormularf::Surface::Back].SetFormular(m_Cube[CubePos::LTB], m_Cube[CubePos::RTB], m_Cube[CubePos::RBB]);
	m_Surface[SFormularf::Surface::Forward].SetFormular(m_Cube[CubePos::RTF], m_Cube[CubePos::LTF], m_Cube[CubePos::LBF]);
	m_Surface[SFormularf::Surface::Right].SetFormular(m_Cube[CubePos::RTB], m_Cube[CubePos::RTF], m_Cube[CubePos::RBF]);
	m_Surface[SFormularf::Surface::Left].SetFormular(m_Cube[CubePos::LTF], m_Cube[CubePos::LTB], m_Cube[CubePos::LBB]);

	m_SphereList.push_front(new CSphere(true, true));
	prev_x =0;
}
CPractice22::~CPractice22()
{
}

void CPractice22::DrawAxis()
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

void CPractice22::DrawCube()
{
	// À­¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::RTF].color.red, m_Cube[CubePos::RTF].color.green, m_Cube[CubePos::RTF].color.blue, m_Cube[CubePos::RTF].color.alpha);
	glVertex3f(m_Cube[CubePos::RTF].x, m_Cube[CubePos::RTF].y, m_Cube[CubePos::RTF].z);
	glVertex3f(m_Cube[CubePos::RTB].x, m_Cube[CubePos::RTB].y, m_Cube[CubePos::RTB].z);
	glVertex3f(m_Cube[CubePos::LTB].x, m_Cube[CubePos::LTB].y, m_Cube[CubePos::LTB].z);
	glVertex3f(m_Cube[CubePos::LTF].x, m_Cube[CubePos::LTF].y, m_Cube[CubePos::LTF].z);
	glEnd();
	// ¿À¸¥ÂÊ¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::RTB].color.red, m_Cube[CubePos::RTB].color.green, m_Cube[CubePos::RTB].color.blue, m_Cube[CubePos::RTB].color.alpha);
	glVertex3f(m_Cube[CubePos::RTB].x, m_Cube[CubePos::RTB].y, m_Cube[CubePos::RTB].z);
	glVertex3f(m_Cube[CubePos::RTF].x, m_Cube[CubePos::RTF].y, m_Cube[CubePos::RTF].z);
	glVertex3f(m_Cube[CubePos::RBF].x, m_Cube[CubePos::RBF].y, m_Cube[CubePos::RBF].z);
	glVertex3f(m_Cube[CubePos::RBB].x, m_Cube[CubePos::RBB].y, m_Cube[CubePos::RBB].z);
	glEnd();
	// ¿ÞÂÊ¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::LTF].color.red, m_Cube[CubePos::LTF].color.green, m_Cube[CubePos::LTF].color.blue, m_Cube[CubePos::LTF].color.alpha);
	glVertex3f(m_Cube[CubePos::LTF].x, m_Cube[CubePos::LTF].y, m_Cube[CubePos::LTF].z);
	glVertex3f(m_Cube[CubePos::LTB].x, m_Cube[CubePos::LTB].y, m_Cube[CubePos::LTB].z);
	glVertex3f(m_Cube[CubePos::LBB].x, m_Cube[CubePos::LBB].y, m_Cube[CubePos::LBB].z);
	glVertex3f(m_Cube[CubePos::LBF].x, m_Cube[CubePos::LBF].y, m_Cube[CubePos::LBF].z);
	glEnd();
	// ¾Õ¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::RBF].color.red, m_Cube[CubePos::RBF].color.green, m_Cube[CubePos::RBF].color.blue, m_Cube[CubePos::RBF].color.alpha);
	glVertex3f(m_Cube[CubePos::RTF].x, m_Cube[CubePos::RTF].y, m_Cube[CubePos::RTF].z);
	glVertex3f(m_Cube[CubePos::LTF].x, m_Cube[CubePos::LTF].y, m_Cube[CubePos::LTF].z);
	glVertex3f(m_Cube[CubePos::LBF].x, m_Cube[CubePos::LBF].y, m_Cube[CubePos::LBF].z);
	glVertex3f(m_Cube[CubePos::RBF].x, m_Cube[CubePos::RBF].y, m_Cube[CubePos::RBF].z);
	glEnd();
	// µÞ¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::LTB].color.red, m_Cube[CubePos::LTB].color.green, m_Cube[CubePos::LTB].color.blue, m_Cube[CubePos::LTB].color.alpha);
	glVertex3f(m_Cube[CubePos::LTB].x, m_Cube[CubePos::LTB].y, m_Cube[CubePos::LTB].z);
	glVertex3f(m_Cube[CubePos::RTB].x, m_Cube[CubePos::RTB].y, m_Cube[CubePos::RTB].z);
	glVertex3f(m_Cube[CubePos::RBB].x, m_Cube[CubePos::RBB].y, m_Cube[CubePos::RBB].z);
	glVertex3f(m_Cube[CubePos::LBB].x, m_Cube[CubePos::LBB].y, m_Cube[CubePos::LBB].z);
	glEnd();
	// ¾Æ·§¸é
	glBegin(GL_QUADS);
	glColor4f(m_Cube[CubePos::LBF].color.red, m_Cube[CubePos::LBF].color.green, m_Cube[CubePos::LBF].color.blue, m_Cube[CubePos::LBF].color.alpha);
	glVertex3f(m_Cube[CubePos::LBF].x, m_Cube[CubePos::LBF].y, m_Cube[CubePos::LBF].z);
	glVertex3f(m_Cube[CubePos::LBB].x, m_Cube[CubePos::LBB].y, m_Cube[CubePos::LBB].z);
	glVertex3f(m_Cube[CubePos::RBB].x, m_Cube[CubePos::RBB].y, m_Cube[CubePos::RBB].z);
	glVertex3f(m_Cube[CubePos::RBF].x, m_Cube[CubePos::RBF].y, m_Cube[CubePos::RBF].z);
	glEnd();
}

void CPractice22::Reset()
{
	m_angle_x = 0.0f;
	m_angle_y = 0.0f;
	m_angle_z = 0.0f;

	m_rotate_x = false;
	m_rotate_y = false;
	m_rotate_z = false;
}

void CPractice22::CheckCollide()
{
	m_Surface[SFormularf::Surface::Top].SetFormular(m_Cube[CubePos::RTF], m_Cube[CubePos::RTB], m_Cube[CubePos::LTB]);
	m_Surface[SFormularf::Surface::Bottom].SetFormular(m_Cube[CubePos::LBF], m_Cube[CubePos::LBB], m_Cube[CubePos::RBB]);
	m_Surface[SFormularf::Surface::Back].SetFormular(m_Cube[CubePos::LTB], m_Cube[CubePos::RTB], m_Cube[CubePos::RBB]);
	m_Surface[SFormularf::Surface::Forward].SetFormular(m_Cube[CubePos::RTF], m_Cube[CubePos::LTF], m_Cube[CubePos::LBF]);
	m_Surface[SFormularf::Surface::Right].SetFormular(m_Cube[CubePos::RTB], m_Cube[CubePos::RTF], m_Cube[CubePos::RBF]);
	m_Surface[SFormularf::Surface::Left].SetFormular(m_Cube[CubePos::LTF], m_Cube[CubePos::LTB], m_Cube[CubePos::LBB]);
	for (auto p : m_SphereList)
	{
		for (int i = 0; i < 6; i++)
		{
			if (m_Surface[i].isCollide(p->GetCenter()))
			{
				p->Collide(m_Surface[i].Normal);
				switch (i)
				{
				case SFormularf::Surface::Top:
					if (m_btop)
					{
						m_Cube[CubePos::RTF].SetColor(255, 0, 0);
					}
					else
					{
						m_Cube[CubePos::RTF].SetColor(0, 255, 0);
					}
					if (m_btop) m_btop = false; else m_btop = true;
					break;
				case SFormularf::Surface::Bottom:
					if (m_bbottom)
					{
						m_Cube[CubePos::LBF].SetColor(0, 255, 255);
					}
					else
					{
						m_Cube[CubePos::LBF].SetColor(255, 0, 0);
					}
					if (m_bbottom) m_bbottom = false; else m_bbottom = true;
					break;
				case SFormularf::Surface::Right:
					if (m_bright)
					{
						m_Cube[CubePos::RTB].SetColor(0, 200, 0);
					}
					else
					{
						m_Cube[CubePos::RTB].SetColor(0, 0, 255);
					}
					if (m_bright) m_bright = false; else m_bright = true;
					break;
				case SFormularf::Surface::Left:
					if (m_bleft)
					{
						m_Cube[CubePos::LTF].SetColor(0, 0, 255);
					}
					else 
					{
						m_Cube[CubePos::LTF].SetColor(0, 255, 0);
					}
					if (m_bleft) m_bleft = false; else m_bleft = true;
					break;
				case SFormularf::Surface::Forward:
					if (m_bforward)
					{
						m_Cube[CubePos::RBF].SetColor(0, 0, 255);
					}
					else
					{
						m_Cube[CubePos::RBF].SetColor(100, 0, 100);
					}
					if (m_bforward) m_bforward = false; else m_bforward = true;
					break;
				case SFormularf::Surface::Back:
					if (m_bback)
					{
						m_Cube[CubePos::LTB].SetColor(255, 255, 0);
					}
					else
					{
						m_Cube[CubePos::LTB].SetColor(0, 150, 0);
					}
					if (m_bback) m_bback = false; else m_bback = true;
					break;
				}
			}
		}
	}
}

bool CPractice22::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice22::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
		if (prev_x == 0)
		{
			prev_x = LOWORD(lParam);
		}
		if (prev_x > LOWORD(lParam))
		{
			prev_x = LOWORD(lParam);
			m_angle_z -= 1.1f;
		}
		else
		{
			prev_x = LOWORD(lParam);
			m_angle_z += 1.1f;
		}
		break;
	}
	return false;
}

bool CPractice22::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice22::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
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
	for (int i = 0; i < 8; i++)
	{
		m_Cube[i].x *= m_scale.x;
		m_Cube[i].y *= m_scale.y;
		m_Cube[i].z *= m_scale.z;
	}
	for (auto p : m_SphereList)
	{
		p->Scale(1.0f, 1.0f, 1.0f);
		p->SetColor(255, 255, 255, 255);
	}
}

void CPractice22::Rendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(m_camera.pos.x, m_camera.pos.y, m_camera.pos.z,
		m_camera.pos.x + m_camera.look.x, m_camera.pos.y + m_camera.look.y, m_camera.pos.z + m_camera.look.z,
		m_camera.up.x, m_camera.up.y, m_camera.up.z);
	glRotatef(m_angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angle_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_angle_z, 0.0f, 0.0f, 1.0f);
	DrawCube();
	for (auto p : m_SphereList)
	{
		p->Rendering();
	}
	DrawAxis();
	glPopMatrix();
}

void CPractice22::Update(float fTimeElapsed)
{
	ProcessInput();
	if (m_rotate_x) m_angle_x += 0.1f;
	if (m_rotate_y) m_angle_y += 0.1f;
	if (m_rotate_z) m_angle_z += 0.1f;
	for (auto p : m_SphereList)
	{
		p->Update(fTimeElapsed);
	}
	CheckCollide();
}

bool CPractice22::ProcessInput()
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
			if (pKeyBuffer['A'] & 0xF0) { bControll = true; m_bAdd = true; }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['N'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_23); }
			else if (pKeyBuffer['B'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_21); }
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
			if (m_bAdd)
			{
				if (m_SphereList.size() < 5)
					m_SphereList.push_front(new CSphere(true, true));
				m_bAdd = false;
			}
			
		}

		return bControll;
	}
	return false;
}
