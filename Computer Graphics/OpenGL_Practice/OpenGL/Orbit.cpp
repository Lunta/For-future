#include "stdafx.h"

#include "Orbit.h"


COrbit::COrbit()
{
	m_rad = rand() % 100;
}
COrbit::~COrbit()
{
}

void COrbit::Rendering(float fScale)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	if (m_bSolid) glutSolidSphere(fScale / 2.0f, 10, 10);
	else glutWireSphere(fScale / 2.0f, 10, 10);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 500; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(fScale*cosf(0.1f*i), 0.0f, fScale*sinf(0.1f*i));
		glVertex3f(fScale*cosf(0.1f*(i + 1)), 0.0f, fScale*sinf(0.1f*(i + 1)));
		glEnd();
	}
	glTranslatef(fScale*cosf(0.1f*m_rad), 0.0f, fScale*sinf(0.1f*m_rad));
	glColor3f(0.0f, 1.0f, 0.0f);
	if (m_bSolid) glutSolidSphere(fScale / 5.0f, 10, 10);
	else glutWireSphere(fScale / 5.0f, 10, 10);
}

void COrbit::Update(float fTimeElapsed)
{
	m_rad += 0.1f;
}

CRevolution::CRevolution()
{
	m_rad_01 = 0.0f;
	m_rad_02 = 0.0f;
	m_rad_03 = 0.0f;
}

CRevolution::~CRevolution()
{
}

void CRevolution::DrawOrbit(float fScale)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 500; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(fScale*cosf(0.1f*i), 0.0f, fScale*sinf(0.1f*i));
		glVertex3f(fScale*cosf(0.1f*(i + 1)), 0.0f, fScale*sinf(0.1f*(i + 1)));
		glEnd();
	}
}

void CRevolution::Rendering(float fScale)
{
	if (m_bSolid) glutSolidSphere(fScale / 5.0f, 10, 10);
	else glutWireSphere(fScale / 5.0f, 10, 10);

	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	DrawOrbit(fScale);
	glTranslatef(fScale*cosf(0.1f*m_rad_01), 0.0f, fScale*sinf(0.1f*m_rad_01));
	glPushMatrix();
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	m_orbit_01.Rendering(fScale/ 10.0f);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	DrawOrbit(fScale);
	glTranslatef(fScale*cosf(0.1f*m_rad_02), 0.0f, fScale*sinf(0.1f*m_rad_02));
	m_orbit_02.Rendering(fScale/ 10.0f);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	DrawOrbit(fScale);
	glTranslatef(fScale*cosf(0.1f*m_rad_03), 0.0f, fScale*sinf(0.1f*m_rad_03)); glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	m_orbit_03.Rendering(fScale/ 10.0f);
	glPopMatrix();
	glPopMatrix();
}

void CRevolution::Update(float fTimeElapsed)
{
	m_orbit_01.Update(fTimeElapsed);
	m_orbit_02.Update(fTimeElapsed);
	m_orbit_03.Update(fTimeElapsed);

	m_rad_01 += 0.15;
	m_rad_02 += 0.05;
	m_rad_03 += 0.1;
}

void CRevolution::SwapType()
{
	if (m_bSolid) m_bSolid = false; 
	else m_bSolid = true;
	m_orbit_01.SwapType();
	m_orbit_02.SwapType();
	m_orbit_03.SwapType();
}
