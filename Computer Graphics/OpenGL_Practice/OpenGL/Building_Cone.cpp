#include"stdafx.h"

#include "Building_Cone.h"



CBuilding_Cone::CBuilding_Cone()
{
	m_Center.x = 0.0f;
	m_Center.y = 0.0f;
	m_Center.z = 0.0f;
	m_Angle.pitch = 0.0f;
	m_Angle.yaw = 0.0f;
	m_Angle.roll = 0.0f;
	m_height = 0.0f;
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
	m_BindingBox[ForwardLeftTop] = { -1.0f,  1.0f,  1.0f };
	m_BindingBox[BackLeftTop] = { -1.0f,  1.0f, -1.0f };
	m_BindingBox[ForwardRightTop] = { 1.0f,  1.0f,  1.0f };
	m_BindingBox[BackRightTop] = { 1.0f,  1.0f, -1.0f };
	m_BindingBox[ForwardLeftDown] = { -1.0f, -1.0f,  1.0f };
	m_BindingBox[BackLeftDown] = { -1.0f, -1.0f, -1.0f };
	m_BindingBox[ForwardRightDown] = { 1.0f, -1.0f,  1.0f };
	m_BindingBox[BackRightDown] = { 1.0f, -1.0f, -1.0f };
}
CBuilding_Cone::~CBuilding_Cone()
{
}

void CBuilding_Cone::Rendering()
{
	glPushMatrix();
	glColor4f(m_Center.color.red / 255.f, m_Center.color.green / 255.f,
		m_Center.color.blue / 255.f, m_Center.color.alpha / 255.f);
	glTranslatef(m_Center.x, m_Center.y, m_Center.z);
	glMultMatrixf(m_matrix);
	glScalef(m_Scale.x, m_Scale.y, m_Scale.z);

	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glutWireCone(1.0f, 1.0f + m_height, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutWireCone(1.0f, 1.0f - m_height, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void CBuilding_Cone::Update(float fTimeElapsed)
{
	if (!m_bflag) m_height += 1.0f * fTimeElapsed;
	else if (m_bflag) m_height -= 1.0f * fTimeElapsed;

	if (m_height > 1.0f) m_bflag = true;
	else if (m_height < -1.0f) m_bflag = false;
}

void CBuilding_Cone::Rotate(float move_angle, bool move_x, bool move_y, float move_z)
{
	glPushMatrix();
	glLoadIdentity();
	if (move_x) glRotatef(move_angle, 1.0f, 0.0f, 0.0f);
	if (move_y) glRotatef(move_angle, 0.0f, 1.0f, 0.0f);
	if (move_z) glRotatef(move_angle, 0.0f, 0.0f, 1.0f);
	glMultMatrixf(m_matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix);
	glPopMatrix();
	m_Angle.pitch += move_angle;
	m_Angle.yaw += move_angle;
	m_Angle.roll += move_angle;
}

void CBuilding_Cone::Translate(float move_x, float move_y, float move_z)
{
	m_Center.x += move_x;
	m_Center.y += move_y;
	m_Center.z += move_z;
	for (int i = 0; i < 8; i++)
	{
		m_BindingBox[i].x += move_x;
		m_BindingBox[i].y += move_y;
		m_BindingBox[i].z += move_z;
	}
}

void CBuilding_Cone::Scale(float scale_x, float scale_y, float scale_z)
{
	m_Scale.x = scale_x;
	m_Scale.y = scale_y;
	m_Scale.z = scale_z;
	for (int i = 0; i < 8; i++)
	{
		m_BindingBox[i].x *= m_Scale.x;
		m_BindingBox[i].y *= m_Scale.y;
		m_BindingBox[i].z *= m_Scale.z;
	}
}

void CBuilding_Cone::SetColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_Center.SetColor(r, g, b);
	m_Center.SetAlpha(a);
}

void CBuilding_Cone::Reset()
{
	m_Center.x = 0.0f;
	m_Center.y = 0.0f;
	m_Center.z = 0.0f;
	m_Angle.pitch = 0.0f;
	m_Angle.yaw = 0.0f;
	m_Angle.roll = 0.0f;
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
}
