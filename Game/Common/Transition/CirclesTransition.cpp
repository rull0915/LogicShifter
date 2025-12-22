#include "CirclesTransition.h"

CirclesTransition::CirclesTransition(float transTime, Transition::Mode mode, int circlesColor, int circlesNum)
	: SceneTransition(transTime, mode)
	, m_circlesColor{ circlesColor }
	, m_circlesNum{ circlesNum }
{
	m_maxRadius = sqrt((Screen::WIDTH / m_circlesNum / 2) * (Screen::WIDTH / m_circlesNum / 2) * 2);
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
	int cell = (Screen::WIDTH / m_circlesNum / 2);

	int posX = -cell, posY = -cell;

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
				DrawCircle(posX, posY, m_maxRadius * Easing::EaseOutQuad(m_elapsedTime / m_transSec), m_circlesColor, true);
				break;
			case Transition::Mode::Out:
				DrawCircle(posX, posY, m_maxRadius * Easing::EaseInQuad(1 - m_elapsedTime / m_transSec), m_circlesColor, true);
				break;
			default:
				break;
			}
		}
	}
}
