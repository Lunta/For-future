#include "stdafx.h"
#include "M_HexTechTower.h"
#include "Boss.h"


CBoss::CBoss()
{
}
CBoss::CBoss(CPlayer * target)
{
	m_vCenter = {0.0f, 1024.0f, 0.0f};
	m_Target = target;
	m_BindingCube.Scale(Vec3f{ 200, 2024.0f, 200 });
}
CBoss::~CBoss()
{
}

void CBoss::Update(const float fTimeElapsed)
{
	m_Model.Update(fTimeElapsed);
	m_vDirection=Normalize(m_Target->GetCenter() - m_vCenter);
}

void CBoss::Rendering()
{
	glPushMatrix();
	glTranslatef(m_vCenter.x, m_vCenter.y, m_vCenter.z);
	glMultMatrixf(m_fRotateMatrix);
	m_Model.Rander();
	glTranslatef(-m_vCenter.x, -m_vCenter.y, -m_vCenter.z);
	m_BindingCube.Rend_BB();
	glPopMatrix();
}

void CBoss::Rotate(const float angle, bool x, bool y, bool z)
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
