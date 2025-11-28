#include "Button.h"

Button::Button(Vector2D pos, Vector2D size, bool mode, int paramator)
	: m_position{ pos }
	, m_size{ size }
	, m_mode{ mode }
	, m_color{ 0 }
	, m_ghButton{ -1 }
	, m_isPressedRight{ false }
{
	if (m_mode)
	{
		m_ghButton = paramator;
	}
	else m_color = paramator;
}

void Button::Initialize()
{
	m_isPressed = false;
	m_isPressedRight = false;

	m_mouseInput = 0;
	m_oldMouseInput = 0;
}

void Button::Update()
{
	m_oldMouseInput = m_mouseInput;
	m_mouseInput = GetMouseInput();

	m_isPressed = false;
	m_isPressedRight = false;

	if((~m_oldMouseInput & m_mouseInput) & MOUSE_INPUT_LEFT)
	{
		Vector2DInt pos;
		GetMousePoint(&pos.x, &pos.y);

		if ((pos.x > m_position.x - m_size.x / 2 && pos.x < m_position.x + m_size.x / 2) &&
			(pos.y > m_position.y - m_size.y / 2 && pos.y < m_position.y + m_size.y / 2)) m_isPressed = true;
	}
	if ((~m_oldMouseInput & m_mouseInput) & MOUSE_INPUT_RIGHT)
	{
		Vector2DInt pos;
		GetMousePoint(&pos.x, &pos.y);

		if ((pos.x > m_position.x - m_size.x / 2 && pos.x < m_position.x + m_size.x / 2) &&
			(pos.y > m_position.y - m_size.y / 2 && pos.y < m_position.y + m_size.y / 2)) m_isPressedRight = true;
	}

}

void Button::Render()
{
	if(m_mode)
	{
		DrawExtendGraph(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, m_ghButton, true);
	}
	else
	{
		MyDrawRoundBoxAA({ m_position.x - m_size.x / 2, m_position.y - m_size.y / 2 }, { m_position.x + m_size.x / 2, m_position.y + m_size.y / 2 }, (m_size.x < m_size.y ? m_size.x : m_size.y) / 10, m_color, true);
	}

	if(m_isPressed)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, 0xffffff, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	Vector2DInt pos;
	GetMousePoint(&pos.x, &pos.y);
}

bool Button::MouseIsOnButton()
{
	Vector2DInt pos;
	GetMousePoint(&pos.x, &pos.y);
	return ((pos.x > m_position.x - m_size.x / 2 && pos.x < m_position.x + m_size.x / 2) &&
		(pos.y > m_position.y - m_size.y / 2 && pos.y < m_position.y + m_size.y / 2));
}
