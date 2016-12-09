#include "stdafx.h"
#include "Cube.h"


CCube::CCube()
{
	m_Center.x = static_cast<float>((rand() % CLIENT_WIDTH)- CLIENT_WIDTH / 2);
	m_Center.y = 0.0f;
	m_Center.z = static_cast<float>((rand() % CLIENT_HEIGHT) - CLIENT_HEIGHT / 2);
	m_scale.x = 20.0f;
	m_scale.y = 20.0f;
	m_scale.z = 20.0f;
	for (int i = 0; i < 16; i++) m_matrix[i] = 0;
	for (int i = 0; i < 4; i++) m_matrix[i * 4 + i] = 1;
	m_Angle.pitch  = rand() % 360;
	m_Angle.yaw    = rand() % 360;
	m_Angle.roll   = rand() % 360;
	Rotate(m_Angle.pitch, true, false, false);
	Rotate(m_Angle.yaw, false, true, false);
	Rotate(m_Angle.roll, false, false, true);
	RotateInit();
	LoadTexture();
}
CCube::~CCube()
{
}
void CCube::RotateInit()
{
	Vec3f temp[8];
	for (int i = 0; i < 8; i++) temp[i] = { 0.0f, 0.0f, 0.0f };
	
	m_Cube[CubePos::LTF] = { -1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::LTB] = { -1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::RTF] = { 1.0f,  1.0f,  1.0f };
	m_Cube[CubePos::RTB] = { 1.0f,  1.0f, -1.0f };
	m_Cube[CubePos::LBF] = { -1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::LBB] = { -1.0f, -1.0f, -1.0f };
	m_Cube[CubePos::RBF] = { 1.0f, -1.0f,  1.0f };
	m_Cube[CubePos::RBB] = { 1.0f, -1.0f, -1.0f };
	for (int i = 0; i < 3; i++)  
		for (int j = 0; j < 3; j++)
		{
			temp[CubePos::LTF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LTF].arr[j];
			temp[CubePos::LTB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LTB].arr[j];
			temp[CubePos::RTF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RTF].arr[j];
			temp[CubePos::RTB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RTB].arr[j];
			temp[CubePos::LBF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LBF].arr[j];
			temp[CubePos::LBB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::LBB].arr[j];
			temp[CubePos::RBF].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RBF].arr[j];
			temp[CubePos::RBB].arr[i] += m_matrix[4 * i + j] * m_Cube[CubePos::RBB].arr[j];
		}
	
	for (int i = 0; i < 8; i++)
	{
		m_Cube[i] = temp[i];
		m_Cube[i].x *= m_scale.x;
		m_Cube[i].y *= m_scale.y;
		m_Cube[i].z *= m_scale.z;
		m_Cube[i] += m_Center;
	}

	m_Normal[DirectionOfSurface::TOP] = Cross(m_Cube[CubePos::RTB] - m_Cube[CubePos::RTF], m_Cube[CubePos::RTB] - m_Cube[CubePos::LTF]);
	m_Normal[DirectionOfSurface::RIGHT] = Cross(m_Cube[CubePos::RTF] - m_Cube[CubePos::RTB], m_Cube[CubePos::RTF] - m_Cube[CubePos::RBB]);
	m_Normal[DirectionOfSurface::LEFT] = Cross(m_Cube[CubePos::LTB] - m_Cube[CubePos::LTF], m_Cube[CubePos::LTB] - m_Cube[CubePos::LBF]);
	m_Normal[DirectionOfSurface::FORWARD] = Cross(m_Cube[CubePos::LTF] - m_Cube[CubePos::RTF], m_Cube[CubePos::LTF] - m_Cube[CubePos::RBF]);
	m_Normal[DirectionOfSurface::BACK] = Cross(m_Cube[CubePos::RTB] - m_Cube[CubePos::LTB], m_Cube[CubePos::RTB] - m_Cube[CubePos::LBB]);
	m_Normal[DirectionOfSurface::BOTTOM] = Cross(m_Cube[CubePos::LBB] - m_Cube[CubePos::LBF], m_Cube[CubePos::LBB] - m_Cube[CubePos::RBF]);
	
	for (int i = 0; i < 6; i++)
		Normalize(m_Normal[i]);
}
void CCube::LoadTexture()
{
	glGenTextures(6, texture_object);
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::TOP]);
	TexBits = LoadDIBitmap("TILE_1.bmp", &BM_Info[DirectionOfSurface::TOP]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT,
		GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::BOTTOM]);
	TexBits = LoadDIBitmap("TILE_2.bmp", &BM_Info[DirectionOfSurface::BOTTOM]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT,
		GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::FORWARD]);
	TexBits = LoadDIBitmap("TILE_3.bmp", &BM_Info[DirectionOfSurface::FORWARD]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT,
		GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::BACK]);
	TexBits = LoadDIBitmap("TILE_4.bmp", &BM_Info[DirectionOfSurface::BACK]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT,
		GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::LEFT]);
	TexBits = LoadDIBitmap("TILE_5.bmp", &BM_Info[DirectionOfSurface::LEFT]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT,
		GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::RIGHT]);
	TexBits = LoadDIBitmap("TILE_6.bmp", &BM_Info[DirectionOfSurface::RIGHT]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT,
		GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

void CCube::Rendering()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	// À­¸é
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::TOP]);
	glBegin(GL_QUADS);
	glNormal3fv(m_Normal[DirectionOfSurface::TOP].arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glEnd();
	// ¿À¸¥ÂÊ¸é
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::RIGHT]);
	glBegin(GL_QUADS);
	glNormal3fv(m_Normal[DirectionOfSurface::RIGHT].arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glEnd();
	// ¿ÞÂÊ¸é
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::LEFT]);
	glBegin(GL_QUADS);
	glNormal3fv(m_Normal[DirectionOfSurface::LEFT].arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glEnd();
	// ¾Õ¸é
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::FORWARD]);
	glBegin(GL_QUADS);
	glNormal3fv(m_Normal[DirectionOfSurface::FORWARD].arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LTF].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RTF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glEnd();
	// µÞ¸é
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::BACK]);
	glBegin(GL_QUADS);
	glNormal3fv(m_Normal[DirectionOfSurface::BACK].arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RTB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LTB].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glEnd();
	// ¾Æ·§¸é
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::BOTTOM]);
	glBegin(GL_QUADS);
	glNormal3fv(m_Normal[DirectionOfSurface::BOTTOM].arr);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::LBB].arr);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::LBF].arr);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(m_Cube[CubePos::RBF].arr);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(m_Cube[CubePos::RBB].arr);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void CCube::Update(const float fTimeElapsed)
{
}

void CCube::Translate(Vec3f move)
{
	m_Center += move;
	for (int i = 0; i < 8; i++)
	{
		m_Cube[i] += move;
	}
}

void CCube::Rotate(float angle, bool x, bool y, bool z)
{
	glPushMatrix();
	glLoadIdentity();
	if (x) glRotatef(angle, 1.0f, 0.0f, 0.0f);
	if (y) glRotatef(angle, 0.0f, 1.0f, 0.0f);
	if (z) glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glMultMatrixf(m_matrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_matrix);
	glPopMatrix();
	m_Angle.pitch += angle;
	m_Angle.yaw += angle;
	m_Angle.roll += angle;
	
	RotateInit();
}

void CCube::Scale(Vec3f scale)
{
	
	m_scale.x = scale.x;
	m_scale.y = scale.y;
	m_scale.z = scale.z;
	RotateInit();
}

bool CCube::isLineCollide(Vec3f * point)
{
	if (point == nullptr) return false;
	Vec3f startpoint = *(point - 1);
	Vec3f endpoint = *point;
	Vec3f dvec = endpoint - startpoint;
	Vec3f checkpoint = { 0.0f, 0.0f, 0.0f };
	Normalize(dvec);

	for (float t = 0.0f; t < Length(endpoint - startpoint); t += 0.1f)
	{
		checkpoint = startpoint + t*dvec;
		if (checkpoint.x < m_Center.x + (m_scale.x*1.4f+10.0f) &&
			checkpoint.x > m_Center.x - (m_scale.x*1.4f+10.0f) &&
			checkpoint.y < m_Center.y + (m_scale.y*1.4f+10.0f) &&
			checkpoint.y > m_Center.y - (m_scale.y*1.4f+10.0f) &&
			checkpoint.z < m_Center.z + (m_scale.z*1.4f+10.0f) &&
			checkpoint.z > m_Center.z - (m_scale.z*1.4f+10.0f))
			return true;
	}
	return false;
}

bool CCube::isPointCollide(Vec3f& point)
{
	if (point.x < m_Center.x + m_scale.x*1.4f &&
		point.x > m_Center.x - m_scale.x*1.4f &&
		point.y < m_Center.y + m_scale.y*1.4f &&
		point.y > m_Center.y - m_scale.y*1.4f &&
		point.z < m_Center.z + m_scale.z*1.4f &&
		point.z > m_Center.z - m_scale.z*1.4f)
		return true;
	return false;
}
