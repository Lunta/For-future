#include "stdafx.h"


#include "Camera_OpenGL.h"



CCamera_OpenGL::CCamera_OpenGL()
{
}

CCamera_OpenGL::CCamera_OpenGL(HWND hWnd, const int client_width, const int client_height)
{
	m_hWnd = hWnd;

	m_Client_Width = client_width;
	m_Client_Height = client_height;

	m_fovy = 60.0f;
	m_aspect = static_cast<double>(m_Client_Width / m_Client_Height);
	m_zNear = 1.0f;
	m_zFar = 3000.0f;
	
	m_Angle = { 0.0f, 0.0f, 0.0f };
	m_Angle.yaw = PI / 2.0f;
	m_Sensitivity = 2.0f;

	m_Pos = { 0.0f, 0.0f, 0.0f };;
	m_Look = { 0.0f, 0.0f, 1.0f };;
	m_Up = { 0.0f, 1.0f, 0.0f };;

	m_TargetPos = { 0.0f, 0.0f, 0.0f };

	m_P_Type = ProjectionType::Perspective;
	m_C_Type = CameraMoveMode::None;
	m_V_Type = CameraViewMode::TPS;

	m_bFixTarget = false;
	m_bShake = false;
}

CCamera_OpenGL::~CCamera_OpenGL()
{
}

void CCamera_OpenGL::Projection()
{
	if (m_P_Type == ProjectionType::Perspective)
		gluPerspective(m_fovy, m_aspect, m_zNear, m_zFar);
	else if (m_P_Type == ProjectionType::Ortho)
		glOrtho(-m_Client_Width / 2, m_Client_Width / 2, -m_Client_Height / 2, m_Client_Height / 2, -1.0, 1.0);
}

void CCamera_OpenGL::LookAt()
{
	gluLookAt(
		m_Pos.x, m_Pos.y, m_Pos.z,
		m_Pos.x + m_Look.x, m_Pos.y + m_Look.y, m_Pos.z + m_Look.z,
		m_Up.x, m_Up.y, m_Up.z);
}

void CCamera_OpenGL::SetProjection(ProjectionType type)
{
	m_P_Type = type;
}

void CCamera_OpenGL::SetTargetPos(const float x, const float y, const float z)
{
	m_TargetPos.x = x;
	m_TargetPos.y = y;
	m_TargetPos.z = z;
}

void CCamera_OpenGL::SetViewMode(CameraViewMode mode)
{
	m_V_Type = mode;
}

void CCamera_OpenGL::FixTarget()
{
	m_bFixTarget = true;
}

void CCamera_OpenGL::ReleaseTarget()
{
	m_bFixTarget = false;
}

void CCamera_OpenGL::TranslatePos(const float side, const float up, const float forward)
{
	m_Pos += m_Look * forward;
	m_Pos.y += up;
	m_Pos -= { cosf(m_Angle.yaw + PI / 2.0f)*side, tanf(m_Angle.pitch)*side, sinf(m_Angle.yaw + PI / 2.0f)*side } ;
}

void CCamera_OpenGL::RotateViewDirection(const int x, const int y)
{	
	std::cout << x << " " << y << std::endl;
	if (m_Client_Width / 2 + 1 < x)
	{
		m_Angle.yaw += m_Sensitivity * radius_per_one_degree;
	}
	else if (m_Client_Width / 2 - 1 > x)
	{
		m_Angle.yaw -= m_Sensitivity * radius_per_one_degree;
	}
	if (m_Client_Height / 2 + 1 < y)
	{
		m_Angle.pitch -= m_Sensitivity * radius_per_one_degree;
	}
	else if (m_Client_Height / 2 - 1> y)
	{
		m_Angle.pitch += m_Sensitivity * radius_per_one_degree;
	}
	if (m_Angle.pitch > (PI / 2.0f) - (PI / 18.0f)) m_Angle.pitch = (PI / 2.0f) - (PI / 18.0f);
	else if (m_Angle.pitch < -(PI / 2.0f) + (PI / 18.0f)) m_Angle.pitch = -(PI / 2.0f) + (PI / 18.0f);
	m_Look = { cosf(m_Angle.yaw), tanf(m_Angle.pitch), sinf(m_Angle.yaw) };
	m_Look.Normalize();
}

void CCamera_OpenGL::TargetTracing(CameraMoveMode mode)
{
	m_C_Type = mode;
}

void CCamera_OpenGL::ZoomScaling(const int scale, const bool smooth)
{
}

void CCamera_OpenGL::ShakeCamera(const float power, const bool axis_x, const bool axis_y)
{
}

void CCamera_OpenGL::Update(float fTimeElapsed)
{
	RECT Rect;
	GetWindowRect(m_hWnd, &Rect);
	SetCursorPos(Rect.left + (m_Client_Width / 2) + 8, Rect.top + (m_Client_Height / 2) + 30);
}

void CCamera_OpenGL::SetSensivity(const float sensitivity)
{
	m_Sensitivity = sensitivity;
}
