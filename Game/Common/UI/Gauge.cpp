#include "Gauge.h"

#include "../Game/Common/MaskManager.h"

Gauge::Gauge(Vector2D pos, Vector2D size, GaugeMode mode, int backColor, int barColor)
	: m_position{ pos }
	, m_size{ size }
	, m_mode{ mode }
	, m_backColor{ backColor }
	, m_barColor{ barColor }
	, m_ratio{ 0 }
{
}

void Gauge::Initialize()
{
	m_ratio = 0;

	m_isMoving = false;
}

void Gauge::Update(float elapsedTime)
{
	if (m_isMoving)
	{
		m_easingX += elapsedTime * 8;

		if (m_easingX >= 1)
		{
			m_isMoving = false;

			m_ratio = m_endRatio;
		}
		else
		{
			m_ratio = m_startRatio + (m_endRatio - m_startRatio) * Easing::EaseOutQuad(m_easingX);
		}
	}
}

void Gauge::Render()
{
	MaskManager::GetInstance().StartDrawMask();
	
	MyDrawRoundBox((m_position - m_size / 2), (m_position + m_size / 2), min(m_size.x, m_size.y) / 4, m_backColor, true);

	MaskManager::GetInstance().FinishDrawMask();

	MaskManager::GetInstance().SetMask(true);

	MyDrawRoundBox((m_position - m_size / 2), (m_position + m_size / 2), min(m_size.x, m_size.y) / 4, m_backColor, true);

	switch (m_mode)
	{
	case GaugeMode::Left:
		DrawBox(m_position.x + m_size.x / 2 - m_ratio * m_size.x, m_position.y - m_size.y / 2 , m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, m_barColor, true);
		break;
	case GaugeMode::Right:
		DrawBox(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x - m_size.x / 2 + m_ratio * m_size.x, m_position.y + m_size.y / 2, m_barColor, true);
		break;
	default:
		break;
	}

	MaskManager::GetInstance().CancelMask();
}

void Gauge::SetRatio(float ratio)
{
	if (!m_isMoving) 
	{
		m_isMoving = true;
		m_easingX = 0;

		m_startRatio = m_ratio;
		m_endRatio = ratio;
	}
}
