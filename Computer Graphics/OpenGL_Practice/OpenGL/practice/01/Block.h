#pragma once
#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include"Vec2f.h"

constexpr float TwoPI = 3.141592653f * 2;
constexpr float PI = 3.141592653f ;
constexpr float Blank = 100.0f;
constexpr int NumOfCycle = 5;

class CBlock
{
public:
	enum class Direction {
		left
		, right
		, top
		, bottom
	};
private:
	float m_x{ 0.0f };
	float m_y{ 0.0f }; 
	float Width{ 0.0f };
	float Height{ 0.0f };
	float m_Gx{ 0.0f };
	float m_Gy{ 0.0f };
	float m_Default_Radian{ 0.0f };
	float m_Radian_CW{ 0.0f };
	float m_Radian_CCW{ 0.0f };
	Vec2f m_dvector;
	Vec2f m_acvector;
	float m_speed{ 0.0f };
	RECT m_rcRect{ 0, 0, 0, 0 };
	float m_R{ 0.0f };
	bool m_bFlip{ false };
	bool m_bRect{ true };
	bool m_bmove{ false };
	bool m_bCW{ false };
	bool m_bPrint{ false };
	bool m_bDie{ false };
	Direction m_direction{ Direction::right };

public:
	CBlock(float x, float y) { m_x = x; m_y = y; m_bRect = true; Width = 40.0f; Height = 20.0f;}
	CBlock(float x, float y, float vx, float vy, float speed, float WinWidth, float WindHeight, int shape) 
	{
		m_x = x; m_y = y; m_dvector.x = vx; m_dvector.y = vy; m_speed = speed; m_rcRect = { 0 ,static_cast<LONG>(WindHeight), static_cast<LONG>(WinWidth), 0 }; m_acvector.x = 0.0f; m_acvector.y = 0.0f;
		if (shape == 1) m_bRect = true; else if (shape == 2) m_bRect = false;
		m_R = Width - 5.0f;
		m_bCW = rand() % 2;
	}
	CBlock(float x, float y, float vx, float vy, float speed, float WinWidth, float WindHeight, int shape, bool randSize = false)
	{
		m_x = x; m_y = y; m_dvector.x = vx; m_dvector.y = vy; m_speed = speed; m_rcRect = { 0 ,static_cast<LONG>(WindHeight), static_cast<LONG>(WinWidth), 0 }; m_acvector.x = 0.0f; m_acvector.y = 0.0f;
		if (shape == 1) m_bRect = true; else if (shape == 2) m_bRect = false;
		m_R = Width - 5.0f;
		m_bCW = rand() % 2;
		if (randSize)
		{
			Width = static_cast<float>(rand() % 100 + 20);
			Height = static_cast<float>(rand() % 100 + 20);
		}
		else
		{
			Width = 40.0f;
			Height = 20.0f;
		}
	}
	~CBlock() {}
	void Flip() { if (m_bFlip == true) { m_bFlip = false; m_R = Width - 5.0f;} else if (m_bFlip == false) { m_bFlip = true; m_R = Height + 5.0f;} }
	void Print() 
	{ 
		if (!m_bDie)
		{
			if(m_bRect)glRectf(GetLeft(), GetBottom(), GetRight(), GetTop()); 
			else
			{
				glBegin(GL_POINTS);
				for (float rad = 0.0f; rad <= 6.28f; rad += 0.01f)
				{
					glVertex2f(m_x + m_R * sin(rad), m_y + m_R * cos(rad));
				}
				glEnd();
			}
		}
	}
	void PrintVortex()
	{
		if (m_bCW)
		{
			glBegin(GL_POINTS);
			for (float rad = 0.0f; rad <= m_Radian_CCW; rad += 0.01f)
			{
				glVertex2f(m_x + (m_Default_Radian + m_R + rad) * sin(rad), m_y + (m_Default_Radian + m_R + rad) * cos(rad));
			}
			for (float rad = 0.0f; rad >= m_Radian_CW; rad -= 0.01f)
			{
				glVertex2f(m_x + (m_Default_Radian + m_R + m_Radian_CCW) * sin(m_Radian_CCW ) * 2 + 
					(m_Default_Radian + m_R - m_Radian_CCW - rad + TwoPI + PI) * sin(rad),
					m_y + (m_Default_Radian + m_R + m_Radian_CCW) * cos(m_Radian_CCW ) * 2 + 
					(m_Default_Radian + m_R - m_Radian_CCW - rad + TwoPI + PI) * cos(rad));
			}
			glEnd();
		}
		else
		{
			glBegin(GL_POINTS);
			for (float rad = 0.0f; rad >= -m_Radian_CCW; rad -= 0.01f)
			{
				glVertex2f(m_x + (m_Default_Radian + m_R + rad + TwoPI + PI) * sin(rad), m_y + (m_Default_Radian + m_R + rad + TwoPI + PI) * cos(rad));
			}
			for (float rad = 0.0f; rad <= -m_Radian_CW; rad += 0.01f)
			{
				glVertex2f(m_x - (m_Default_Radian + m_R + m_Radian_CCW) * sin(-m_Radian_CCW) * 2 +
					(m_Default_Radian + m_R - m_Radian_CCW + rad + TwoPI + PI) * sin(rad - PI),
					m_y - (m_Default_Radian + m_R + m_Radian_CCW) * cos(-m_Radian_CCW) * 2 +
					(m_Default_Radian + m_R - m_Radian_CCW + rad + TwoPI + PI) * cos(rad - PI));
			}
			glEnd();
		}
	}
	void Slow() { m_speed -= 50.0f; if (m_speed < 0) m_speed = 0.0f; }
	void Fast() { m_speed += 50.0f; }
	const bool GetFlip() { return m_bFlip; }
	const float GetLeft() { if (m_bFlip) return (m_x - Width / 2); else return (m_x - Height / 2); }
	const float GetTop() { if (m_bFlip) return (m_y + Height / 2); else return (m_y + Width / 2); }
	const float GetRight() { if (m_bFlip) return (m_x + Width / 2); else return (m_x + Height / 2); }
	const float GetBottom() { if (m_bFlip) return (m_y - Height / 2); else return (m_y - Width / 2); }
	const bool CheckMove(float x, float y) { if (x > GetLeft() && x < GetRight() && y > GetBottom() && y < GetTop()) { m_bmove = true; return true; } return false; }
	void SetMove(bool boolean) { m_bmove = boolean; }
	void SetMove(float vx, float vy, float speed) 
	{ 
		float l = sqrt((vx - m_x)*(vx - m_x) + (vy - m_y)*(vy - m_y));
		m_dvector.x = (vx - m_x) / l;
		m_dvector.y = (vy - m_y) / l;
		m_speed = speed;
		m_Gx = vx;
		m_Gy = vy;
	}
	void Update_five() 
	{
		m_acvector.x += m_dvector.x * m_speed;
		m_acvector.y += m_dvector.y * m_speed;
		
		if (m_acvector.x > 1)
		{
			m_x += m_acvector.x;
			m_acvector.x = 0.0f;
		}
		if (m_acvector.x <-1) 
		{
			m_x += m_acvector.x;
			m_acvector.x = 0.0f;
		}
		if (m_acvector.y > 1) 
		{
			m_y += m_acvector.y;
			m_acvector.y = 0.0f;
		}
		if (m_acvector.y <-1) 
		{
			m_y += m_acvector.y;
			m_acvector.y = 0.0f;
		}
		if (m_x > m_rcRect.right || m_x < m_rcRect.left) m_dvector.x = -m_dvector.x;
		if (m_y > m_rcRect.top || m_y < m_rcRect.bottom) m_dvector.y = -m_dvector.y;
	}
	void Update_six()
	{
		if (m_bmove)
		{
			 switch (m_direction)
			{
			case Direction::right:
				m_x += m_speed;
				m_acvector.x += m_speed;
				if (m_acvector.x < m_speed && m_acvector.x + m_speed > 0.0f)
				{
					m_x -= m_acvector.x ;
					m_acvector.x = 0.0f;
					m_bmove = false;
					m_direction = Direction::right;
				}
				if (m_x > m_rcRect.right)
				{
					m_x = m_rcRect.right;
					m_acvector.x -= m_x - m_rcRect.right;
					m_direction = Direction::bottom;
				}
				break;
			case Direction::bottom:
				m_y -= m_speed;
				m_acvector.y -= m_speed;
				if (m_y < m_rcRect.bottom)
				{
					m_y = m_rcRect.bottom;
					m_acvector.y -= m_rcRect.left - m_y;
					m_direction = Direction::left;
				}
				break;
			case Direction::left:
				m_x -= m_speed;
				m_acvector.x -= m_speed;
				if (m_x < m_rcRect.left)
				{
					m_x = m_rcRect.left;
					m_acvector.x -= m_rcRect.left - m_x;
					m_direction = Direction::top;
				}
				break;
			case Direction::top:
				m_y += m_speed;
				m_acvector.y += m_speed;
				if (m_acvector.y > 0)
				{
					m_y -= m_acvector.y + m_speed;
					m_acvector.y = 0.0f;
					m_direction = Direction::right;
				}
				break;
			}
		}
	}
	void Update_seven()
	{
		m_R += 1.0f;
	}
	void Update_eight()
	{
		m_x += m_dvector.x * m_speed;
		m_y += m_dvector.y * m_speed;
		if (m_x - m_Gx > -10.0f && m_x - m_Gx < 10.0f ||
			m_y - m_Gy > -10.0f && m_y - m_Gy < 10.0f)
		{
			SetMove(0.0f, 0.0f, 0.0f);
		}
	}
	void Update_nine()
	{
		//m_Default_Radian += 0.02f;
		if(!m_bPrint) m_Radian_CCW += 0.02f;
		else m_Radian_CW -= 0.02f;
		//if (m_Radian_CCW > TwoPI * NumOfCycle) m_Radian_CCW = 0.0f;
		if (m_Radian_CCW > TwoPI * NumOfCycle)
		{
			m_Radian_CCW = TwoPI * NumOfCycle;
			m_Radian_CW = 0.0f;
			m_bPrint = true;
		}
		//if (m_Radian_CW < -TwoPI * NumOfCycle) m_Radian_CW = 0.0f;
		if (m_Radian_CW < -TwoPI * NumOfCycle)
		{
			m_Radian_CW = -TwoPI * NumOfCycle;
			m_Radian_CCW = 0.0f;
			m_Radian_CW = 0.0f;
			m_bPrint = false;
		}
		//if (m_Default_Radian > TwoPI) m_Default_Radian = 0.0f;
	}
	void Update_ten()
	{
		m_acvector.x += m_dvector.x * m_speed;
		m_acvector.y += m_dvector.y * m_speed;

		if (m_acvector.x > 1)
		{
			m_x += m_acvector.x;
			m_acvector.x = 0.0f;
		}
		if (m_acvector.x <-1)
		{
			m_x += m_acvector.x;
			m_acvector.x = 0.0f;
		}
		if (m_acvector.y > 1)
		{
			m_y += m_acvector.y;
			m_acvector.y = 0.0f;
		}
		if (m_acvector.y <-1)
		{
			m_y += m_acvector.y;
			m_acvector.y = 0.0f;
		}
		if (m_x > m_rcRect.right - Blank || m_x < m_rcRect.left + Blank) m_bDie = true;
		if (m_y > m_rcRect.top - Blank || m_y < m_rcRect.bottom + Blank) m_bDie = true;
	}
};

