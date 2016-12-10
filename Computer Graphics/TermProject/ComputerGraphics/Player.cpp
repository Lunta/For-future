#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
	m_vDirection = { 0.0f, 0.0f, 1.0f };
}
CPlayer::~CPlayer()
{
}

void CPlayer::RotateToDirection(Vec3f & look, Vec3f& angle)
{
	m_Angle = angle;
	m_Angle.y -= PI * 0.5f;

	for (int i = 0; i < 16; i++) m_fRotateMatrix[i] = 0;
	for (int i = 0; i < 4; i++) m_fRotateMatrix[i * 4 + i] = 1;
	glPushMatrix();
	glLoadIdentity();
	glRotatef(-m_Angle.x*degree_per_one_radius, 1.0f, 0.0f, 0.0f);
	glMultMatrixf(m_fRotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_fRotateMatrix);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	glRotatef(-m_Angle.y*degree_per_one_radius, 0.0f, 1.0f, 0.0f);
	glMultMatrixf(m_fRotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_fRotateMatrix);
	glPopMatrix();
	m_vDirection = look;
}

void CPlayer::Update(const float fTimeElapsed)
{
	m_Model.Update(fTimeElapsed);
}

void CPlayer::Rendering()
{
	glPushMatrix();
	glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
	glMultMatrixf(m_fRotateMatrix);
	m_Model.Rander();
	glTranslatef(-m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
	m_BindingCube.Rend_BB();
	glPopMatrix();
}

void CPlayer::Rotate(const float angle, bool x, bool y, bool z)
{
	glPushMatrix();
	glLoadIdentity();
	if (x)
	{
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		m_Angle.x += angle;
	}
	if (y)
	{
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		m_Angle.y += angle;
	}
	if (z)
	{
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		m_Angle.z += angle;
	}
	glMultMatrixf(m_fRotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_fRotateMatrix);
	glPopMatrix();
}
