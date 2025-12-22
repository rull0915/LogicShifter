#include "Mouse.h"

int m_mouseInput = GetMouseInput();
int m_oldMouseInput = -1;

Vector2DInt m_mousePos = {0, 0};
Vector2DInt m_oldMousePos = {0, 0};

float mouseWheelRot = 0;

MouseMode m_mouseDrawMode = MouseMode::Normal;

void MouseUpdate()
{
	m_oldMouseInput = m_mouseInput;
	m_mouseInput = GetMouseInput();

	m_oldMousePos = m_mousePos;
	GetMousePoint(&m_mousePos.x, &m_mousePos.y);

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

