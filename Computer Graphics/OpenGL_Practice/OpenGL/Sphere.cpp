#include "stdafx.h"

#include "Sphere.h"


CSphere::CSphere(bool autoMove, bool Solid)
{
	m_Field = 0.0f;
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

	m_DirectVector = { static_cast<float>((rand() % 100) / 100.0f),static_cast<float>((rand() % 100) / 100.0f),static_cast<float>((rand() % 100) / 100.0f) };
	m_DirectVector.Normalize();
	m_Speed = 80.0f;
	m_bAutoMove = autoMove;
	m_bSolid = Solid;
}
CSphere::~CSphere()
{
}

void CSphere::Rendering()
{
	glPushMatrix();
	glColor4f(m_Center.color.red / 255.f, m_Center.color.green / 255.f, 
		m_Center.color.blue / 255.f, m_Center.color.alpha / 255.f);
	glTranslatef(m_Center.x, m_Center.y, m_Center.z);
	glMultMatrixf(m_matrix);
	glScalef(m_Scale.x, m_Scale.y, m_Scale.z);
	if (m_bSolid) glutSolidSphere(1.0f, 10, 10);
	else glutWireSphere(1.0f, 10, 10);
	glPopMatrix();
	//DrawBindingBox();
}

void CSphere::Update(float fTimeElapsed)
{
	if (m_bAutoMove)
	{
		Translate(
			m_DirectVector.x * m_Speed * fTimeElapsed, 
			m_DirectVector.y * m_Speed * fTimeElapsed, 
			m_DirectVector.z * m_Speed * fTimeElapsed);
	}
}

void CSphere::DrawBindingBox()
{
	glBegin(GL_LINE_STRIP);
	glVertex3f(m_BindingBox[ForwardLeftTop].x, 
		m_BindingBox[ForwardLeftTop].y, 
		m_BindingBox[ForwardLeftTop].z);
	glVertex3f(m_BindingBox[BackLeftTop].x, 
		m_BindingBox[BackLeftTop].y, 
		m_BindingBox[BackLeftTop].z);
	glVertex3f(m_BindingBox[ForwardRightTop].x, 
		m_BindingBox[ForwardRightTop].y, 
		m_BindingBox[ForwardRightTop].z);
	glVertex3f(m_BindingBox[BackRightTop].x, 
		m_BindingBox[BackRightTop].y, 
		m_BindingBox[BackRightTop].z);
	glVertex3f(m_BindingBox[ForwardLeftDown].x, 
		m_BindingBox[ForwardLeftDown].y, 
		m_BindingBox[ForwardLeftDown].z);
	glVertex3f(m_BindingBox[BackLeftDown].x, 
		m_BindingBox[BackLeftDown].y, 
		m_BindingBox[BackLeftDown].z);
	glVertex3f(m_BindingBox[ForwardRightDown].x, 
		m_BindingBox[ForwardRightDown].y, 
		m_BindingBox[ForwardRightDown].z);
	glVertex3f(m_BindingBox[BackRightDown].x, 
		m_BindingBox[BackRightDown].y,
		m_BindingBox[BackRightDown].z);
	glEnd();
}

void CSphere::move(float move_angle, bool move_x, bool move_y, float move_z)
{
	float move_distance = (move_angle / 360.0f) * (2.0f * PI * m_Scale.x);
	if (move_x) 
	{
		Translate(0.0f, 0.0f, move_distance);
		Rotate(move_angle, move_x, move_y, move_z);
	}
	if (move_y)
	{
		//Translate(0.0f, move_distance, 0.0f);
		Rotate(move_angle, move_x, move_y, move_z);
	}
	if (move_z)
	{
		Translate(-move_distance, 0.0f, 0.0f);
		Rotate(move_angle, move_x, move_y, move_z);
	}
}
void CSphere::Collide(const Vec3f& SurfaceNormal)
{
	m_DirectVector = m_DirectVector - 2 * SurfaceNormal * DotProduct(m_DirectVector, SurfaceNormal);
	m_DirectVector.Normalize();
	Translate(
		m_DirectVector.x,
		m_DirectVector.y,
		m_DirectVector.z);
}

void CSphere::Rotate(float move_angle, bool move_x, bool move_y, float move_z)
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

void CSphere::Translate(float move_x, float move_y, float move_z)
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
	
	//if (m_Center.x < -m_Field) m_Center.x = -m_Field;
	//if (m_Center.y < -m_Field) m_Center.y = -m_Field;
	//if (m_Center.z < -m_Field) m_Center.z = -m_Field;
	//if (m_Center.x > m_Field) m_Center.x = m_Field;
	//if (m_Center.y > m_Field) m_Center.y = m_Field;
	//if (m_Center.z > m_Field) m_Center.z = m_Field;
}

void CSphere::Scale(float scale_x, float scale_y, float scale_z)
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

void CSphere::SetColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_Center.SetColor(r, g, b);
	m_Center.SetAlpha(a);
}

void CSphere::Reset()
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
