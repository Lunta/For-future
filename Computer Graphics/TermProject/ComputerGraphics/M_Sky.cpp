#include "stdafx.h"
#include "M_Sky.h"


CM_Sky::CM_Sky()
{
}

CM_Sky::CM_Sky(CTextureLibraray * texture)
{
	m_TextureLib = texture;
}
CM_Sky::~CM_Sky()
{
}

bool CM_Sky::Update(const float fTimeElapsed)
{
	m_angle += 60.0f * fTimeElapsed;
	if (m_angle > 360.0f) m_angle - 360.0f;
	return false;
}

void CM_Sky::Rander()
{
	glPushMatrix();
	{
		glRotatef(-90, 1, 0, 0);

		CTextureLibraray::UsingTexture2D();
		{
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

			m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::BK_STORM);
			glColor3f(1.0, 1.0, 1.0);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

			glutSolidSphere(m_size, 256, 128);

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
		}
		CTextureLibraray::StopUsingTexture2D();

	}
	glPopMatrix();
	

	

}
