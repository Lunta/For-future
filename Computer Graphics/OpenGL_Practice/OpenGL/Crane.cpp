#include "stdafx.h"

#include "Crane.h"


CCrane::CCrane()
{
	m_Center.x = 0.0f;
	m_Center.y = 0.0f;
	m_Center.z = 0.0f;
	m_Angle.pitch = 0.0f;
	m_Angle.yaw = 0.0f;
	m_Angle.roll = 0.0f;
	m_rotate_arm_x = 0.0f;
	m_rotate_arm_z = 0.0f;
	m_rotate_armbody_x = 0.0f;
	m_rotate_armbody_y = 0.0f;
	m_ratate_wheelbody_y = 0.0f;
	m_translate = 0.0f;
	m_timer = 0.0f;
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
	for (int i = 0; i < 4; i++) m_Wheel[i].SetField(400.0f);

	m_BindingBox[ForwardLeftTop]	= { -0.4f,  0.5f,  0.5f };
	m_BindingBox[BackLeftTop]		= { -0.4f,  0.5f, -0.5f };
	m_BindingBox[ForwardRightTop]	= {  0.4f,  0.5f,  0.5f };
	m_BindingBox[BackRightTop]		= {  0.4f,  0.5f, -0.5f };
	m_BindingBox[ForwardLeftDown]	= { -0.4f, -0.5f,  0.5f };
	m_BindingBox[BackLeftDown]		= { -0.4f, -0.5f, -0.5f };
	m_BindingBox[ForwardRightDown]	= {  0.4f, -0.5f,  0.5f };
	m_BindingBox[BackRightDown]		= {  0.4f, -0.5f, -0.5f };

	m_WheelBody.Scale(0.5f, 0.2f, 1.0f);
	m_WheelBody.Translate(0.0f, -0.2f, 0.0f);

	m_ArmBody.Scale(0.35f, 0.2f, 0.6f);
	m_ArmBody.Translate(0.0f, 0.0f, 0.0f);

	m_Arm.Scale(0.1f, 0.5f, 0.1f);
	m_Arm.Translate(0.0f, 0.3f, 0.0f);

	m_Wheel[0].Scale(0.05f, 0.1f, 0.1f);
	m_Wheel[0].Translate(0.25f, -0.3f, 0.4f);
	m_Wheel[1].Scale(0.05f, 0.1f, 0.1f);
	m_Wheel[1].Translate(-0.25f, -0.3f, 0.4f);
	m_Wheel[2].Scale(0.05f, 0.1f, 0.1f);
	m_Wheel[2].Translate(0.25f, -0.3f, -0.4f);
	m_Wheel[3].Scale(0.05f, 0.1f, 0.1f);
	m_Wheel[3].Translate(-0.25f, -0.3f, -0.4f);

	SetWheelBodyColor(255, 0, 0, 255);
	SetArmBodyColor(255, 255, 0, 255);
	SetArmColor(0, 255, 255, 255);
	SetWheelColor(255, 0, 255, 255);
}
CCrane::~CCrane()
{
}

void CCrane::Rotate_Arm(float angle, bool x, bool z)
{
	if (x) m_rotate_arm_x += angle;
	if (z) m_rotate_arm_z += angle;
}

void CCrane::Rotate_ArmBody(float angle, bool x, bool y)
{
	if (x) m_rotate_armbody_x += angle;
	if (y) m_rotate_armbody_y += angle;
}

void CCrane::Rotate_WheelBody(float angle)
{
	m_ratate_wheelbody_y += angle;
}

void CCrane::DrawBindingBox()
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

void CCrane::Stop(bool stop)
{
	m_stop = stop;
}

void CCrane::Rendering(bool wheel)
{
	glPushMatrix();
	glColor4f(m_Center.color.red / 255.f, m_Center.color.green / 255.f,
		m_Center.color.blue / 255.f, m_Center.color.alpha / 255.f);
	glTranslatef(m_Center.x, m_Center.y, m_Center.z);
	
	glMultMatrixf(m_matrix);
	glScalef(m_Scale.x, m_Scale.y, m_Scale.z);

	glPushMatrix(); 
	glRotatef(m_ratate_wheelbody_y, 0.0f, 1.0f, 0.0f);
	m_WheelBody.Rendering();
	glPopMatrix();

	glPushMatrix();
	glRotatef(m_ratate_wheelbody_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotate_armbody_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotate_armbody_y, 0.0f, 1.0f, 0.0f);
	m_ArmBody.Rendering();
	glPopMatrix();

	glPushMatrix();
	glRotatef(m_ratate_wheelbody_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotate_armbody_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotate_armbody_y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotate_arm_x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotate_arm_z, 0.0f, 0.0f, 1.0f);
	m_Arm.Rendering();
	glPopMatrix();
	
	if (wheel)
	{
		glPushMatrix();
		glRotatef(m_ratate_wheelbody_y, 0.0f, 1.0f, 0.0f);

		m_Wheel[0].Rendering();
		m_Wheel[1].Rendering();
		m_Wheel[2].Rendering();
		m_Wheel[3].Rendering();
		glPopMatrix();
	}
	glPopMatrix();
	//DrawBindingBox();
}

void CCrane::Update(float fTimeElapsed)
{
	if (m_stop)
	{
		m_stopTimer += fTimeElapsed;
		if (m_stopTimer > 0.5f)
		{
			m_stop = false;
			m_stopTimer = 0.0f;
		}
		return;
	}
	m_timer += fTimeElapsed;
	if (m_timer > 20) m_timer = 0.0f;
	else if (m_timer <= 10)
	{
		m_Wheel[0].Rotate(0.1f, true, false, false);
		m_Wheel[1].Rotate(0.1f, true, false, false);
		m_Wheel[2].Rotate(0.1f, true, false, false);
		m_Wheel[3].Rotate(0.1f, true, false, false);
		m_translate += (0.1f / 360.0f) * (2.0f * PI * 0.05f);
		Translate(0.0f, 0.0f, (0.1f / 360.0f) * (2.0f * PI * 0.05f) * m_Scale.z);
	}
	else if (m_timer > 10)
	{
		m_Wheel[0].Rotate(-0.1f, true, false, false);
		m_Wheel[1].Rotate(-0.1f, true, false, false);
		m_Wheel[2].Rotate(-0.1f, true, false, false);
		m_Wheel[3].Rotate(-0.1f, true, false, false);
		m_translate += -(0.1f / 360.0f) * (2.0f * PI * 0.05f);
		Translate(0.0f, 0.0f, -(0.1f / 360.0f) * (2.0f * PI * 0.05f) * m_Scale.z);
	}
}

void CCrane::Rotate(float move_angle, bool move_x, bool move_y, float move_z)
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
void CCrane::Translate(float move_x, float move_y, float move_z)
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
void CCrane::Scale(float scale_x, float scale_y, float scale_z)
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

void CCrane::SetColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_Center.SetColor(r, g, b);
	m_Center.SetAlpha(a);

	m_Arm.SetColor(r, g, b, a);
	m_ArmBody.SetColor(r, g, b, a);
	m_WheelBody.SetColor(r, g, b, a);
	for (int i = 0; i < 4; i++) m_Wheel[i].SetColor(r, g, b, a);
}
void CCrane::SetWheelBodyColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_WheelBody.SetColor(r, g, b, a);
}
void CCrane::SetArmBodyColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_ArmBody.SetColor(r, g, b, a);
}
void CCrane::SetArmColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	m_Arm.SetColor(r, g, b, a);
}
void CCrane::SetWheelColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	for (int i = 0; i < 4; i++) m_Wheel[i].SetColor(r, g, b, a);
}

void CCrane::Reset()
{
	//m_BindingBox[ForwardLeftTop] = { -0.4f,  0.5f,  0.5f };
	//m_BindingBox[BackLeftTop] = { -0.4f,  0.5f, -0.5f };
	//m_BindingBox[ForwardRightTop] = { 0.4f,  0.5f,  0.5f };
	//m_BindingBox[BackRightTop] = { 0.4f,  0.5f, -0.5f };
	//m_BindingBox[ForwardLeftDown] = { -0.4f, -0.5f,  0.5f };
	//m_BindingBox[BackLeftDown] = { -0.4f, -0.5f, -0.5f };
	//m_BindingBox[ForwardRightDown] = { 0.4f, -0.5f,  0.5f };
	//m_BindingBox[BackRightDown] = { 0.4f, -0.5f, -0.5f };
	m_Center.x = 0.0f;
	m_Center.y = 0.0f;
	m_Center.z = 0.0f;
	m_Angle.pitch = 0.0f;
	m_Angle.yaw = 0.0f;
	m_Angle.roll = 0.0f;
	m_rotate_arm_x = 0.0f;
	m_rotate_arm_z = 0.0f;
	m_rotate_armbody_x = 0.0f;
	m_rotate_armbody_y = 0.0f;
	m_ratate_wheelbody_y = 0.0f;
	m_timer = 0.0f;
	m_translate = 0.0f;
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
}
