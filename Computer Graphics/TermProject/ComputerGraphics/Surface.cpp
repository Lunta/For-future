#include "stdafx.h"
#include "Surface.h"


CSurface::CSurface()
{
	SetSurface_XZ();
	LoadTexture();
}
CSurface::~CSurface()
{
}

void CSurface::LoadTexture()
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

void CSurface::Rendering()
{
	float t = Reciprocal(DETAIL);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_object[DirectionOfSurface::BOTTOM]);
	glColor4f(1, 1, 1, 1);
	for (int i = 0; i < DETAIL - 1; i++)
	{
		for (int j = 0; j < DETAIL - 1; j++)
		{
			glBegin(GL_QUADS);
			glNormal3fv(m_normal[i][j].arr);
			glTexCoord2f(t*j, t*(i+1));
			glVertex3fv(m_vertex[i][j].arr);
			glTexCoord2f(t*j, t*i);
			glVertex3fv(m_vertex[i + 1][j].arr);
			glTexCoord2f(t*(j+1), t*i);
			glVertex3fv(m_vertex[i + 1][j + 1].arr);
			glTexCoord2f(t*(j+1), t*(i+1));
			glVertex3fv(m_vertex[i][j + 1].arr);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CSurface::Update(const float fTimeElapsed)
{
}

void CSurface::SetScale(const float x, const float y, const float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
	for (int i = 0; i < DETAIL; i++)
	{
		for (int j = 0; j < DETAIL; j++)
		{
			m_vertex[i][j].x *= m_Scale.x;
			m_vertex[i][j].y *= m_Scale.y;
			m_vertex[i][j].z *= m_Scale.z;
		}
	}
}

void CSurface::SetSurface_XZ()
{
	float t = Reciprocal(DETAIL);
	
	for (int i = 0; i < DETAIL; i++)
	{
		for (int j = 0; j < DETAIL; j++)
		{
			float y = -static_cast<float>(rand() % 2) *
				static_cast<float>(rand() % 100) * 0.01f;
			m_vertex[i][j] = 
			{ -(t*(DETAIL *0.5f)) + (t * j),
				y, -(t*(DETAIL *0.5f)) + (t * i) };
		}
	}
	for (int i = 0; i < DETAIL; i++)
	{
		for (int j = 0; j < DETAIL; j++)
		{
			m_vertex[i][j].x *= m_Scale.x;
			m_vertex[i][j].y *= m_Scale.y;
			m_vertex[i][j].z *= m_Scale.z;
		}
	}
	for (int i = 0; i < DETAIL - 1; i++)
	{
		for (int j = 0; j < DETAIL - 1; j++)
		{
			m_normal[i][j] = Normalize(Cross(
				m_vertex[i][j] - m_vertex[i + 1][j],
				m_vertex[i][j] - m_vertex[i + 1][j + 1]));

		}
	}
}

void CSurface::SetSurface_XY()
{
}

void CSurface::SetSurface_YZ()
{
}
