#include "Mouse.h"

int m_mouseInput = GetMouseInput();
int m_oldMouseInput = -1;

Vector2DInt m_mousePos = {0, 0};
Vector2DInt m_oldMousePos = {0, 0};

float mouseWheelRot = 0;

void MouseUpdate()
{
	m_oldMouseInput = m_mouseInput;
	m_mouseInput = GetMouseInput();

	m_oldMousePos = m_mousePos;
	GetMousePoint(&m_mousePos.x, &m_mousePos.y);

	mouseWheelRot = GetMouseWheelRotVolF();
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

