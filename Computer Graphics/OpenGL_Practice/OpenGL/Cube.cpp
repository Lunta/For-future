#include "stdafx.h"

#include "Cube.h"



CCube::CCube()
{
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
}
CCube::~CCube()
{
}

void CCube::Rendering()
{
	glPushMatrix();
	glColor4f(m_Center.color.red / 255.f, m_Center.color.green / 255.f,
		m_Center.color.blue / 255.f, m_Center.color.alpha / 255.f);
	glTranslatef(m_Center.x, m_Center.y, m_Center.z);
	glMultMatrixf(m_matrix);
	glScalef(m_Scale.x, m_Scale.y, m_Scale.z);
	glutSolidCube(1.0f);
	glPopMatrix();
}

void CCube::Update(float fTimeElapsed)
{
}

void CCube::Rotate(float move_angle, bool move_x, bool move_y, float move_z)
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

void CCube::Translate(float move_x, float move_y, float move_z)
{
	m_Center.x += move_x;
	m_Center.y += move_y;
	m_Center.z += move_z;
}

void CCube::Scale(float scale_x, float scale_y, float scale_z)
{
	m_Scale.x = scale_x;
	m_Scale.y = scale_y;
	m_Scale.z = scale_z;
}

void CCube::SetColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_Center.SetColor(r, g, b);
	m_Center.SetAlpha(a);
}

void CCube::Reset()
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
