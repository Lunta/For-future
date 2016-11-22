#include"stdafx.h"


#include "Building_Torus.h"



CBuilding_Torus::CBuilding_Torus()
{
	m_Center.x = 0.0f;
	m_Center.y = 0.0f;
	m_Center.z = 0.0f;
	m_Angle.pitch = 0.0f;
	m_Angle.yaw = 0.0f;
	m_Angle.roll = 0.0f;
	m_traslate = 0.0f;
	m_body.Scale(0.2f, 1.0f, 0.2f);
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
	m_BindingBox[ForwardLeftTop] = { -0.2f,  1.0f,  0.2f };
	m_BindingBox[BackLeftTop] = { -0.2f,  1.0f, -0.2f };
	m_BindingBox[ForwardRightTop] = { 0.2f,  1.0f,  0.2f };
	m_BindingBox[BackRightTop] = { 0.2f,  1.0f, -0.2f };
	m_BindingBox[ForwardLeftDown] = { -0.2f, -1.0f,  0.2f };
	m_BindingBox[BackLeftDown] = { -0.2f, -1.0f, -0.2f };
	m_BindingBox[ForwardRightDown] = { 0.2f, -1.0f,  0.2f };
	m_BindingBox[BackRightDown] = { 0.2f, -1.0f, -0.2f };
}
CBuilding_Torus::~CBuilding_Torus()
{
}

void CBuilding_Torus::Rendering()
{
	glPushMatrix();
	glColor4f(m_Center.color.red / 255.f, m_Center.color.green / 255.f,
		m_Center.color.blue / 255.f, m_Center.color.alpha / 255.f);
	glTranslatef(m_Center.x, m_Center.y, m_Center.z);
	glMultMatrixf(m_matrix);
	glScalef(m_Scale.x, m_Scale.y, m_Scale.z);

	m_body.Rendering();
	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, m_traslate);
	glScalef(0.3f, 0.3f, 0.1f);
	glutWireTorus(0.8f, 1.0f, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void CBuilding_Torus::Update(float fTimeElapsed)
{
	if (!m_bflag) m_traslate += 1.0f * fTimeElapsed;
	else if (m_bflag) m_traslate -= 1.0f * fTimeElapsed;

	if (m_traslate > 0.5f) m_bflag = true;
	else if (m_traslate < -0.5f) m_bflag = false;
}

void CBuilding_Torus::Rotate(float move_angle, bool move_x, bool move_y, float move_z)
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

void CBuilding_Torus::Translate(float move_x, float move_y, float move_z)
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

void CBuilding_Torus::Scale(float scale_x, float scale_y, float scale_z)
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

void CBuilding_Torus::SetColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_Center.SetColor(r, g, b);
	m_Center.SetAlpha(a);
	m_body.SetColor(r, g, b, a);
}

void CBuilding_Torus::Reset()
{
	m_Center.x = 0.0f;
	m_Center.y = 0.0f;
	m_Center.z = 0.0f;
	m_Angle.pitch = 0.0f;
	m_Angle.yaw = 0.0f;
	m_traslate = 0.0f;
	m_Angle.roll = 0.0f;
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
}
