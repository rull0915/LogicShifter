#include "Mouse.h"

int m_mouseInput = GetMouseInput();
int m_oldMouseInput = -1;

Vector2DInt m_mousePos = {0, 0};
Vector2DInt m_oldMousePos = {0, 0};

float mouseWheelRot = 0;

float m_mouseSensitivity = 0.9f;

MouseMode m_mouseDrawMode = MouseMode::Normal;

void MouseUpdate()
{
	// 中心からの移動量を取得
	int x = 0, y = 0;
	GetMousePoint(&x, &y);

	int diffX = x - (Screen::WIDTH / 2), diffY = y - (Screen::HEIGHT / 2);

	// マウス座標を中心に固定
	SetMousePoint(Screen::WIDTH / 2, Screen::HEIGHT / 2);

	// ゲーム内の仮想座標
	static Vector2D virtualMousePos = Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT / 2 };
	virtualMousePos += Vector2D{ static_cast<float>(diffX), static_cast<float>(diffY) } * m_mouseSensitivity;

	// 画面内に補正
	if (virtualMousePos.x < 0) virtualMousePos.x = 0;
	if (virtualMousePos.y < 0) virtualMousePos.y = 0;

	if (virtualMousePos.x > Screen::WIDTH) virtualMousePos.x = (float)Screen::WIDTH;
	if (virtualMousePos.y > Screen::HEIGHT) virtualMousePos.y = (float)Screen::HEIGHT;

	// 使用する座標の更新
	m_oldMousePos = m_mousePos;
	m_mousePos = Vector2DInt{ static_cast<int>(virtualMousePos.x), static_cast<int>(virtualMousePos.y) };

	m_oldMouseInput = m_mouseInput;
	m_mouseInput = GetMouseInput();

	mouseWheelRot = GetMouseWheelRotVolF();
}

void MouseRender()
{
	int x = 0, y = 0;

	switch (m_mouseDrawMode)
	{
	case MouseMode::Normal:
		x = 128;
		y = 128;
		break;
	case MouseMode::Erase:
		x = 144;
		y = 112;
		break;
	case MouseMode::Move:
		x = 304;
		y = 96;
		break;
	default:
		break;
	}

	DrawRectExtendGraph(m_mousePos.x, m_mousePos.y, m_mousePos.x + 32, m_mousePos.y + 32,
		x, y, 16, 16,
		m_ghMouseCursors, true);
}

int MouseDown()
{
	return (~m_oldMouseInput & m_mouseInput);
}

int MouseEnter()
{
	return m_mouseInput;
}

int MouseUp()
{
	return (~m_mouseInput & m_oldMouseInput);
}

Vector2DInt GetMouseMoveValue()
{
	return { m_oldMousePos - m_mousePos };
}

float MouseWheelRot()
{
	return mouseWheelRot;
}

