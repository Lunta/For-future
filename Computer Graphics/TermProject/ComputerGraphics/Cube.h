#pragma once
class CCube
{
private:

	Vec3f m_Center;
	Vec3f m_Cube[8];
	Vec3f m_Normal[6];

	Scale3f m_scale; 
	Angle3f m_Angle;
	float m_matrix[16];

	GLubyte * TexBits;
	BITMAPINFO *BM_Info[6];
	GLuint texture_object[6];
public:
	CCube();
	~CCube();

	void RotateInit();
	void LoadTexture();

	void Rendering();
	void Update(const float fTimeElapsed);

	void Translate(Vec3f move);
	void Rotate(float angle, bool x, bool y, bool z);
	void Scale(Vec3f scale);

	bool isLineCollide(Vec3f * point);
	bool isPointCollide(Vec3f& point);

	const Vec3f GetCenter() const { return m_Center; }
	const Vec3f* Get_BB() const { return m_Cube; }
};

