#include "CirclesTransition.h"

CirclesTransition::CirclesTransition(float transTime, Transition::Mode mode, int circlesColor, int circlesNum)
	: SceneTransition(transTime, mode)
	, m_circlesColor{ circlesColor }
	, m_circlesNum{ circlesNum }
{
	m_maxRadius = sqrtf((static_cast<float>(Screen::WIDTH) / m_circlesNum / 2) * (static_cast<float>(Screen::WIDTH) / m_circlesNum / 2) * 2);
}

void CirclesTransition::Initialize()
{
}

bool CirclesTransition::Update(float elapsedTime)
{
	// Œo‰ßŽžŠÔ‚Ì‰ÁŽZ
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_transSec) m_elapsedTime = m_transSec;

	// ‘JˆÚŽžŠÔ‚ð’´‚¦‚½‚©‚Ç‚¤‚©
	return (m_elapsedTime >= m_transSec);
}

void CirclesTransition::Render()
{
	float cell = (static_cast<float>(Screen::WIDTH / m_circlesNum / 2));

	float posX = -cell, posY = -cell;

	while (posY < Screen::HEIGHT)
	{
		posY += cell * 2;

		posX = -cell;

		while (posX < Screen::WIDTH)
		{
			posX += cell * 2;

			switch (m_mode)
			{
			case Transition::Mode::In:
				DrawCircleAA(posX, posY, m_maxRadius * Easing::EaseOutQuad(m_elapsedTime / m_transSec), m_circlesColor, true);
				break;
			case Transition::Mode::Out:
				DrawCircleAA(posX, posY, m_maxRadius * Easing::EaseInQuad(1 - m_elapsedTime / m_transSec), m_circlesColor, true);
				break;
			default:
				break;
			}
		}
	}
}
