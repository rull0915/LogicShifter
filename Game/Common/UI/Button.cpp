#include "Button.h"
#include "../Game/Common/MaskManager.h"

Button::Button(Vector2D pos, Vector2D size, bool mode, int paramator, bool isRounding)
	: m_position{ pos }
	, m_size{ size }
	, m_mode{ mode }
	, m_color{ 0 }
	, m_ghButton{ -1 }
	, m_isPressedRight{ false }
	, m_pressedOnMe{ false }
	, m_pressedOnMeRight{ false }
	, m_isRounding{ isRounding }
{
	if (m_mode)
	{
		m_ghButton = paramator;
	}
	else m_color = paramator;
}

Button::~Button()
{
}

void Button::Initialize()
{
	m_isPressed = false;
	m_isPressedRight = false;

	m_pressedOnMe = false;
	m_pressedOnMeRight = false;
}

void Button::Update()
{
	m_isPressed = false;
	m_isPressedRight = false;

	if (MouseDown() & MOUSE_INPUT_LEFT  && MouseIsOnButton()) m_pressedOnMe = true;
	if (MouseDown() & MOUSE_INPUT_RIGHT && MouseIsOnButton()) m_pressedOnMeRight = true;

	// 左クリックが離されたら
	if(MouseUp() & MOUSE_INPUT_LEFT)
	{
		if (MouseIsOnButton() && m_pressedOnMe)
		{
			Sound::Play(Sound::Type::Decide, DX_PLAYTYPE_BACK);

			m_isPressed = true;
		}
		m_pressedOnMe = false;
	}
	// 右クリックが離されたら
	if (MouseUp() & MOUSE_INPUT_RIGHT)
	{
		if (MouseIsOnButton() && m_pressedOnMeRight) m_isPressedRight = true;
		m_pressedOnMeRight = false;
	}

}

void Button::Render()
{
	MaskManager::GetInstance().StartDrawMask();

	ShapeRender();

	MaskManager::GetInstance().FinishDrawMask();

	MaskManager::GetInstance().SetMask(true);

	ShapeRenderAA();

	if (MouseIsOnButton())
	{		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);

		if(MouseEnter() & MOUSE_INPUT_LEFT) DrawBoxAA(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, GetColor(70, 70, 90), true);
		else DrawBoxAA(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, GetColor(220, 220, 240), true);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	MaskManager::GetInstance().CancelMask();
}

void Button::Finalize()
{
}

bool Button::MouseIsOnButton()
{
	return ((m_mousePos.x > m_position.x - m_size.x / 2 && m_mousePos.x < m_position.x + m_size.x / 2) &&
		(m_mousePos.y > m_position.y - m_size.y / 2 && m_mousePos.y < m_position.y + m_size.y / 2));
}

void Button::ShapeRender()
{
	if (m_mode)
	{
		DrawExtendGraphF(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, m_ghButton, true);
	}
	else
	{
		if (m_isRounding) MyDrawRoundBox(
			ToVector2DInt({ m_position.x - m_size.x / 2, m_position.y - m_size.y / 2 }), 
			ToVector2DInt({ m_position.x + m_size.x / 2, m_position.y + m_size.y / 2 }),
			static_cast<int>((m_size.x < m_size.y ? m_size.x : m_size.y) / 10), m_color, true);
		else DrawBoxAA(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, m_color, true);
	}
}

void Button::ShapeRenderAA()
{
	if (m_mode)
	{
		DrawExtendGraphF(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, m_ghButton, true);
	}
	else
	{
		if (m_isRounding) MyDrawRoundBox(
			ToVector2DInt({ m_position.x - m_size.x / 2, m_position.y - m_size.y / 2 }), 
			ToVector2DInt({ m_position.x + m_size.x / 2, m_position.y + m_size.y / 2 }), 
			static_cast<int>((m_size.x < m_size.y ? m_size.x : m_size.y) / 10), m_color, true);
		else DrawBoxAA(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, m_color, true);
	}
}
