#pragma once
class CM_Sky
{
private:
	float m_size{ 2048.0f };
	float m_angle{};
	CTextureLibraray* m_TextureLib;
public:
	CM_Sky();
	CM_Sky(CTextureLibraray *texture);
	~CM_Sky();

	bool Update(const float fTimeElapsed);
	void Rander();

};

