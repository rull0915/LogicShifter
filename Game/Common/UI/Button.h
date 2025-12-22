#pragma once

class Button
{
	int m_color;
	int m_ghButton;

	bool m_mode;

	Vector2D m_position;

	Vector2D m_size;

	bool m_isPressed;
	bool m_isPressedRight;

	bool m_pressedOnMe;
	bool m_pressedOnMeRight;

	// ŠÛ‚ß‚é‚©‚Ç‚¤‚©
	bool m_isRounding;

public:
	Button(Vector2D pos, Vector2D size, bool mode, int paramator, bool isRounding = true);
	~Button();

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	bool GetIsPressed() const { return m_isPressed; }
	bool GetIsPressedRight() const { return m_isPressedRight; }

	void ChengePos(Vector2D pos) { m_position = pos; }
	void ChengeColor(int color) { m_color = color; }

	Vector2D GetPos() const { return m_position; }

	bool MouseIsOnButton();

private:
	void ShapeRender();
	void ShapeRenderAA();
};

