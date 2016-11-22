#include "stdafx.h"

#include "MainScene.h"
#include "Practice12.h"



CPractice12::CPractice12()
{
	m_rad = 0.0f;
	m_ratate_rad = 0.0f;
	m_size = 0.1f;
	m_mode = Mode::Normal;
	m_fInputTimer = 0.0f;
}
CPractice12::~CPractice12()
{
}

void CPractice12::DrawBK()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
}

void CPractice12::DrawFigure()
{
	if (m_bTriangle)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0f, m_size / 2, 0.0f);
		glVertex3f(m_size / 2, -m_size / 2, 0.0f);
		glVertex3f(-m_size / 2, -m_size / 2, 0.0f);
		glEnd();
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(m_size / 2, m_size / 2, 0.0f);
		glVertex3f(- m_size / 2, m_size / 2, 0.0f);
		glVertex3f(- m_size / 2, - m_size / 2, 0.0f);
		glVertex3f(m_size / 2, - m_size / 2, 0.0f);
		glEnd();
	}
	
}

void CPractice12::Reset()
{
	m_MouseInput.clear();
	m_Center = { 0, 0 };
	m_x = 0.0f;
	m_y = 0.0f;
	m_rad = 0.0f;
	m_size = 0.0f;

	m_ratate_rad = 0.0f;

	m_bRotate = false;
	m_bUp = false;
	m_bMove = false;
}

void CPractice12::ModeNormal()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 65; i++)
	{
		glVertex3f(0.5f * cosf(0.1f * i), 0.5f * sinf(0.1f * i), 0.0f);
		glVertex3f(0.5f * cosf(0.1f * (i + 1)), 0.5f * sinf(0.1f * (i + 1)), 0.0f);
	}
	glEnd();
	if (m_bRotate)
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(m_x, m_y, 0.0f);
		glRotatef(33 * (m_rad * PI * 0.55555555f), 0.0f, 0.0f, 1.0f);
		DrawFigure();
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(m_x, m_y, 0.0f);
		DrawFigure();
		glPopMatrix();
	}
}

void CPractice12::ModeSin()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 500; i++)
	{
		glVertex3f(0.002f * i - 0.5f, 0.1f * sinf(0.1f * i), 0.0f);
		glVertex3f(0.002f * (i + 1) - 0.5f,  0.1f*sinf(0.1f * (i + 1)), 0.0f);
	}
	glEnd();
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glTranslatef(m_x, m_y, 0.0f);
	DrawFigure();
	glPopMatrix();
}

void CPractice12::ModeSpring()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 500; i++)
	{
		glVertex3f(0.1f * cosf(0.1f * i) + 0.002f * i - 0.5f, 0.1f * sinf(0.1f * i ), 0.0f);
		glVertex3f(0.1f * cosf(0.1f * (i + 1)) + 0.002f * (i + 1) - 0.5f, 0.1f * sinf(0.1f * (i + 1)), 0.0f);
	}
	glEnd();
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glTranslatef(m_x + 0.1f * cosf(m_rad), m_y, 0.0f);
	DrawFigure();
	glPopMatrix();
}

void CPractice12::ModeZigzag()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(-0.4f, -0.1f, 0.0f);
	glVertex3f(-0.2f, 0.1f, 0.0f);
	glVertex3f(0.0f, -0.1f, 0.0f);
	glVertex3f(0.2f, 0.1f, 0.0f);
	glVertex3f(0.4f, -0.1f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-0.5f, 0.0f, 0.0f);
	glTranslatef(m_x, m_y, 0.0f);
	DrawFigure();
	glPopMatrix();
	
}

void CPractice12::ModeFree()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (auto p : m_MouseInput)
	{
		glVertex3f(p->x, p->y, 0.0f);
	}
	glEnd();
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(m_x, m_y, 0.0f);
	DrawFigure();
	glPopMatrix();
	
}

bool CPractice12::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

bool CPractice12::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	float w, h;
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		if (m_mode == Mode::Free)
		{
			if (!m_bMove)
			{
				w = CLIENT_WIDTH / 2;
				h = CLIENT_HEIGHT / 2;
				m_MouseInput.push_back(new Vec2f(static_cast<float>((LOWORD(lParam) - w) / w), -static_cast<float>((HIWORD(lParam) - h) / h)));
				if (m_MouseInput.size() > 5) m_MouseInput.pop_front();
			}
		}
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		if (m_mode == Mode::Free)
		{
			if (m_bMove)
			{
				m_bMove = false;
				Reset();
			}
			else m_bMove = true;
			m_vec_idx = 0;
			m_Center = { 0.0f, 0.0f };
			int i = 0;
			Vec2f prevVec;
			for (auto p : m_MouseInput)
			{
				if (i == 0)m_vec[i] = ((*p) - m_Center);
				else m_vec[i] = ((*p) - prevVec);
				m_vec[i].Normalize();
				prevVec = *p;
				i++;
			}
		}
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return false;
}

bool CPractice12::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

void CPractice12::BuildPractice(CMainScene * CurrentScene, HWND hWnd, CurrentPractice tag)
{
	CPractice::BuildPractice(CurrentScene, hWnd, tag);
}

void CPractice12::Rendering()
{
	DrawBK();
	switch (m_mode)
	{
	case Mode::Normal:
		ModeNormal();
		break;
	case Mode::Sin:
		ModeSin();
		break;
	case Mode::Spring:
		ModeSpring();
		break;
	case Mode::Zigzag:
		ModeZigzag();
		break;
	case Mode::Free:
		ModeFree();
		break;
	}
	
}

void CPractice12::Update(float fTimeElapsed)
{
	m_fInputTimer += fTimeElapsed;
	if (m_fInputTimer > 0.2f)
	{
		ProcessInput();
		m_fInputTimer = 0.0f;
	}
	switch (m_mode)
	{
	case Mode::Normal:
		m_x = 0.5f * cosf(m_rad);
		m_y = 0.5f * sinf(m_rad);
		m_rad += 0.0008f;
		m_ratate_rad += 0.005f;
		break;
	case Mode::Sin:
		m_rad += 0.001f;
		m_x += 0.00002f;
		m_y = 0.1f * sinf(m_rad);
		break;
	case Mode::Spring:
		m_rad += 0.001f;
		m_x += 0.00002f;
		m_y = 0.1f * sinf(m_rad);
		break;
	case Mode::Zigzag:
		m_x += 0.00002f;
		if (m_bUp)
			m_y += 0.00002f;
		else
			m_y -= 0.00002f;
		if (m_y > 0.1f) m_bUp = false;
		else if (m_y < -0.1f) m_bUp = true;
		break;
	case Mode::Free:
		if (m_bMove)
		{
			m_x +=m_vec[m_vec_idx].x * 0.0002f;
			m_y +=m_vec[m_vec_idx].y * 0.0002f;
			int i = 0;
			for (auto p : m_MouseInput)
			{
				if (i == m_vec_idx)
				{
					Vec2f temp;
					temp.x = p->x - m_x;
					temp.y = p->y - m_y;
					if (temp.Length() < 0.001f)
						m_vec_idx++;
				}
				i++;
			}
		}
		break;
	}
	if (m_size > 0.09f) m_size = 0.08f;
	else m_size = 0.1f;
}

bool CPractice12::ProcessInput()
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
			
			if (pKeyBuffer[VK_NUMPAD0] & 0xF0) { bControll = true; m_mode = Mode::Normal; Reset(); }
			else if (pKeyBuffer[VK_NUMPAD1] & 0xF0) { bControll = true; m_mode = Mode::Sin; Reset();}
			else if (pKeyBuffer[VK_NUMPAD2] & 0xF0) { bControll = true; m_mode = Mode::Spring; Reset();}
			else if (pKeyBuffer[VK_NUMPAD3] & 0xF0) { bControll = true; m_mode = Mode::Zigzag; Reset();}
			else if (pKeyBuffer[VK_NUMPAD4] & 0xF0) { bControll = true; m_mode = Mode::Free; Reset();}
			else if (pKeyBuffer['C'] & 0xF0) { bControll = true; if (m_bTriangle) m_bTriangle = false; else m_bTriangle = true; }
			else if (pKeyBuffer['R'] & 0xF0) { bControll = true; if (m_bRotate) m_bRotate = false; else m_bRotate = true; m_ratate_rad = 0.0f;}
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true; PostQuitMessage(0); }
			else if (pKeyBuffer['M'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_13);}
			else if (pKeyBuffer['V'] & 0xF0) { bControll = true; m_pScene->ChangePractice(CPractice::CurrentPractice::Practice_11); }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true;  }
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
