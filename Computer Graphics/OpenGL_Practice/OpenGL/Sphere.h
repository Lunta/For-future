#pragma once
class CSphere
{
private:
	Vertex3f m_Center;
	Angle3f m_Angle;
	Scale3f m_Scale;
	Vertex3f m_BindingBox[8];
	float m_matrix[16];

	bool m_bSolid;

	Vec3f m_DirectVector;
	float m_Speed;
	bool m_bAutoMove;

	float m_Field;

public:
	CSphere(bool autoMove = false, bool Solid = false);
	~CSphere();

	void Rendering();
	void Update(float fTimeElapsed);

	void DrawBindingBox();

	void move(float move_angle, bool move_x, bool move_y, float move_z);
	void Collide(const Vec3f& SurfaceNormal);

	void Rotate(float move_angle, bool move_x, bool move_y, float move_z);
	void Translate(float move_x, float move_y, float move_z);
	void Scale(float scale_x, float scale_y, float scale_z);

	void SetField(float scale = 100.0f) { m_Field = scale; }
	void SetColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);

	Vertex3f* GetBB() { return m_BindingBox; }
	Vertex3f GetCenter() { return m_Center; }

	void Reset();
};

