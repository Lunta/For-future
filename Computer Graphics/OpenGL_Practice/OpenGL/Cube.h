#pragma once
class CCube
{
private:
	Vertex3f m_Center;
	Angle3f m_Angle;
	Scale3f m_Scale;
	float m_matrix[16];

public:
	CCube();
	~CCube();

	void Rendering();
	void Update(float fTimeElapsed);

	void Rotate(float move_angle, bool move_x, bool move_y, float move_z);
	void Translate(float move_x, float move_y, float move_z);
	void Scale(float scale_x, float scale_y, float scale_z);

	void SetColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);

	void Reset();

	Vertex3f GetCenter() { return m_Center; }
};

