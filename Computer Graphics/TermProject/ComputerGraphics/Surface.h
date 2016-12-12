#pragma once
#define DETAIL 100
//��#define CurveDetail 0.01f

template< typename T > constexpr float Reciprocal(T x) { return 1.0f / static_cast<float>(x); }

class CSurface
{
private:
	CTextureLibraray *m_TextureLib;
	Vec3f m_Center;
	Vec3f m_vertex[DETAIL][DETAIL];
	//Vec3f m_CurvedSurface[DETAIL*DETAIL][DETAIL*DETAIL]; // ����, Ǯ������
	Vec3f m_normal[DETAIL - 1][DETAIL - 1];
	Scale3f m_Scale;

public:
	CSurface();
	CSurface(CTextureLibraray *texture);
	~CSurface();

	void Rendering();
	void Update(const float fTimeElapsed);

	void SetScale(const float x, const float y, const float z);
	void SetSurface_XZ();
	void SetSurface_XY();
	void SetSurface_YZ();

};

