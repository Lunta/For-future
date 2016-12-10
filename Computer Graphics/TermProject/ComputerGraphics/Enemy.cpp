#include "stdafx.h"
#include "M_CombatDrone.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
}

CEnemy::CEnemy(Vec3f &pos, CPlayer * target)
{
	m_vCenter = pos;
	m_Target = target;
	m_BindingCube.Scale(Vec3f{42, 42, 42});
}
CEnemy::~CEnemy()
{
}

void CEnemy::Update(const float fTimeElapsed)
{
	m_Model.Update(fTimeElapsed);
	m_BindingCube.SetPos(m_vCenter);
	m_Timer += fTimeElapsed;
	if (m_Timer > Turning_Speed)
	{
		m_vDirection = Normalize(m_vDirection + Normalize(m_Target->GetCenter() - m_vCenter));
		m_Timer = 0.0f;
	}
	m_vCenter += m_speed * m_vDirection * fTimeElapsed;
}

void CEnemy::Rendering()
{
	glPushMatrix();
	glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
	glMultMatrixf(m_fRotateMatrix);
	m_Model.Rander();
	glTranslatef(-m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
	m_BindingCube.Rend_BB();
	glPopMatrix();
}

void CEnemy::Rotate(const float angle, bool x, bool y, bool z)
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
