#include "ClockTransition.h"
#include "../Game/Common/MaskManager.h"

ClockTransition::ClockTransition(float transTime, Transition::Mode mode, int clockColor, Vector2D centerPos)
	: SceneTransition(transTime, mode)
	, m_clockColor{ clockColor }
	, m_centerPos{ centerPos }
	, m_angle{ 0 }
{
}

ClockTransition::~ClockTransition()
{
}

void ClockTransition::Initialize()
{
	m_maxRadius = Screen::WIDTH + Screen::HEIGHT;
}

bool ClockTransition::Update(float elapsedTime)
{
	// Œo‰ßŽžŠÔ‚Ì‰ÁŽZ
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_transSec) m_elapsedTime = m_transSec;

	m_angle = 2 * DX_PI_F * Easing::EaseInQuad(m_elapsedTime / m_transSec);

	// ‘JˆÚŽžŠÔ‚ð’´‚¦‚½‚©‚Ç‚¤‚©
	return (m_elapsedTime >= m_transSec);
}

void ClockTransition::Render()
{
	switch (m_mode)
	{
	case Transition::Mode::In:

		ClockRender();

		break;
	case Transition::Mode::Out:

		MaskManager::GetInstance().StartDrawMask();

		ClockRender();

		MaskManager::GetInstance().FinishDrawMask();

		MaskManager::GetInstance().SetMask(false);

		DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, m_clockColor, true);

		MaskManager::GetInstance().CancelMask();

		break;
	default:
		break;
	}
}

void ClockTransition::ClockRender()
{
	if (m_angle >= DX_PI_F * (0.0f / 4) && m_angle < DX_PI_F * (1.0f / 4))
	{
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(m_centerPos.x, 0, pos.x, pos.y, m_centerPos.x, m_centerPos.y, m_clockColor, true);
	}
	else if (m_angle >= DX_PI_F * (1.0f / 4) && m_angle < DX_PI_F * (2.0f / 4))
	{
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(DX_PI_F / 4), -cosf(DX_PI_F / 4) };
		Vector2D pos2 = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(m_centerPos.x, 0, pos.x, pos.y, m_centerPos.x, m_centerPos.y, m_clockColor, true);
		DrawTriangle(pos2.x, pos2.y, pos.x, pos.y, m_centerPos.x, m_centerPos.y, m_clockColor, true);
	}
	else if (m_angle >= DX_PI_F * (2.0f / 4) && m_angle < DX_PI_F * (3.0f / 4))
	{
		DrawBox(m_centerPos.x, 0, Screen::WIDTH, m_centerPos.y, m_clockColor, true);
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(m_centerPos.x, m_centerPos.y, Screen::WIDTH, m_centerPos.y, pos.x, pos.y, m_clockColor, true);
	}
	else if (m_angle >= DX_PI_F * (3.0f / 4) && m_angle < DX_PI_F * (4.0f / 4))
	{
		DrawBox(m_centerPos.x, 0, Screen::WIDTH, m_centerPos.y, m_clockColor, true);
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(DX_PI_F * (3.0f / 4)), -cosf(DX_PI_F * (3.0f / 4)) };
		DrawTriangle(m_centerPos.x, m_centerPos.y, Screen::WIDTH, m_centerPos.y, pos.x, pos.y, m_clockColor, true);
		Vector2D pos2 = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(pos2.x, pos2.y, pos.x, pos.y, m_centerPos.x, m_centerPos.y, m_clockColor, true);
	}
	else if (m_angle >= DX_PI_F * (4.0f / 4) && m_angle < DX_PI_F * (5.0f / 4))
	{
		DrawBox(m_centerPos.x, 0, Screen::WIDTH, Screen::HEIGHT, m_clockColor, true);
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(m_centerPos.x, m_centerPos.y, m_centerPos.x, Screen::HEIGHT, pos.x, pos.y, m_clockColor, true);
	}
	else if (m_angle >= DX_PI_F * (5.0f / 4) && m_angle < DX_PI_F * (6.0f / 4))
	{
		DrawBox(m_centerPos.x, 0, Screen::WIDTH, Screen::HEIGHT, m_clockColor, true);
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(DX_PI_F * (5.0f / 4)), -cosf(DX_PI_F * (5.0f / 4)) };
		DrawTriangle(m_centerPos.x, m_centerPos.y, m_centerPos.x, Screen::HEIGHT, pos.x, pos.y, m_clockColor, true);
		Vector2D pos2 = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(pos2.x, pos2.y, pos.x, pos.y, m_centerPos.x, m_centerPos.y, m_clockColor, true);
	}
	else if (m_angle >= DX_PI_F * (6.0f / 4) && m_angle < DX_PI_F * (7.0f / 4))
	{
		DrawBox(m_centerPos.x, 0, Screen::WIDTH, Screen::HEIGHT, m_clockColor, true);
		DrawBox(0, m_centerPos.y, m_centerPos.x, Screen::HEIGHT, m_clockColor, true);
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(m_centerPos.x, m_centerPos.y, 0, m_centerPos.y, pos.x, pos.y, m_clockColor, true);
	}
	else
	{
		DrawBox(m_centerPos.x, 0, Screen::WIDTH, Screen::HEIGHT, m_clockColor, true);
		DrawBox(0, m_centerPos.y, m_centerPos.x, Screen::HEIGHT, m_clockColor, true);
		Vector2D pos = m_centerPos + m_maxRadius * Vector2D{ sinf(DX_PI_F * (7.0f / 4)), -cosf(DX_PI_F * (7.0f / 4)) };
		DrawTriangle(m_centerPos.x, m_centerPos.y, 0, m_centerPos.y, pos.x, pos.y, m_clockColor, true);
		Vector2D pos2 = m_centerPos + m_maxRadius * Vector2D{ sinf(m_angle), -cosf(m_angle) };
		DrawTriangle(pos2.x, pos2.y, pos.x, pos.y, m_centerPos.x, m_centerPos.y, m_clockColor, true);
	}
}
