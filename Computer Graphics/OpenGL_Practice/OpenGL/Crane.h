#pragma once
class CCrane
{	
private:
	CCube m_Arm;
	CCube m_ArmBody;
	CCube m_WheelBody;

	CSphere m_Wheel[4];

	Vertex3f m_Center;
	Angle3f m_Angle;
	Scale3f m_Scale;

	Vertex3f m_BindingBox[8];

	float m_matrix[16];

	float m_rotate_arm_x;
	float m_rotate_arm_z;

	float m_rotate_armbody_x;
	float m_rotate_armbody_y;

	float m_ratate_wheelbody_y;

	float m_timer;
	float m_translate;

	float m_stopTimer = 0.0f;
	bool m_stop = false;

public:
	CCrane();
	~CCrane();

	void Rotate_Arm(float angle, bool x, bool z);
	void Rotate_ArmBody(float angle, bool x, bool y);
	void Rotate_WheelBody(float angle);

	void DrawBindingBox();
	
	void Stop(bool stop = true);

	void Rendering(bool wheel = false);
	void Update(float fTimeElapsed);

	void Rotate(float move_angle, bool move_x, bool move_y, float move_z);
	void Translate(float move_x, float move_y, float move_z);
	void Scale(float scale_x, float scale_y, float scale_z);

	void SetColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);
	void SetWheelBodyColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);
	void SetArmBodyColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);
	void SetArmColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);
	void SetWheelColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);

	Vertex3f* GetBB() { return m_BindingBox; }
	Vertex3f GetCenter() { return m_Center; }

	void Reset();
};

