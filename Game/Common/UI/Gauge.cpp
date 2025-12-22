#include "Gauge.h"

Gauge::Gauge(Vector2D pos, Vector2D size, GaugeMode mode, int backColor, int barColor)
	: m_position{ pos }
	, m_size{ size }
	, m_mode{ mode }
	, m_backColor{ backColor }
	, m_barColor{ barColor }
	, m_ratio{ 0 }
	, m_maskScreen{ -1 }
{
}

void Gauge::Initialize()
{
	m_ratio = 0;

	if(m_maskScreen == -1) m_maskScreen = MakeScreen(Screen::WIDTH, Screen::HEIGHT, TRUE);

	// マスク機能の初期化を行う
	CreateMaskScreen();

	// 作成したスクリーンをマスク用グラフィックとして登録する
	SetMaskScreenGraph(m_maskScreen);

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
	// 描画先をマスク用の画像に変更
	SetDrawScreen(m_maskScreen);

	// マスク用の画像をクリア
	ClearDrawScreen();

	MyDrawRoundBox((m_position - m_size / 2), (m_position + m_size / 2), min(m_size.x, m_size.y) / 4, m_backColor, true);

	SetMaskReverseEffectFlag(1);

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseMaskScreenFlag(TRUE);

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

	SetMaskReverseEffectFlag(0);

	SetUseMaskScreenFlag(FALSE);
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
