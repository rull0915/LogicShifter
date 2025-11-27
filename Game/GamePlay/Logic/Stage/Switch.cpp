#include "Switch.h"

Switch::Switch(bool& change, Vector2D pos, Vector2D size)
	: m_changed{ change }
	, m_position{ pos }
	, m_size{ size }
	, m_easingX{ 0 }
	, m_nowState{ State::Off }
{

}

void Switch::Initialize()
{
	m_nowState = State::Off;

	m_changed = false;

	m_easingX = 0;
}

void Switch::Update(float elapsedTime)
{
	// クリックされたら
	if(MouseDown() & MOUSE_INPUT_LEFT)
	{
		// かつマウスがスイッチ上にあれば
		if (OnMe({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) }))
		{
			// 状態遷移
			if (m_nowState == State::On)
			{
				m_nowState = State::ToOff;

				// 変数をfalseに
				 m_changed = false;
			}
			else if (m_nowState == State::Off)
			{
				m_nowState = State::ToOn;

				// 変数をtrueに
				 m_changed = true;
			}
		}
	}

	// 状態で分岐
	switch (m_nowState)
	{
		// オンの時
	case Switch::State::On:
		// イージング変数を初期化
		m_easingX = 0;
		break;
	case Switch::State::Off:
		// イージング変数を初期化
		m_easingX = 0;
		break;
	case Switch::State::ToOn:
		// イージングの加算
		m_easingX += elapsedTime * 8;
		
		// 1を超えたら
		if(m_easingX >= 1)
		{
			// ONへ移行
			m_nowState = State::On;
		}
		break;
	case Switch::State::ToOff:
		// イージングの加算
		m_easingX += elapsedTime * 8;

		// 1を超えたら
		if(m_easingX >= 1)
		{
			m_nowState = State::Off;
		}
		break;
	default:
		break;
	}
}

void Switch::Render()
{
	// 円の位置
	Vector2D circlePos1 = Vector2D{ m_position.x - m_size.x / 2 + m_size.y / 2, m_position.y };
	Vector2D circlePos2 = Vector2D{ m_position.x + m_size.x / 2 - m_size.y / 2, m_position.y };

	// 矩形のサイズ
	Vector2D rectSize = { m_size.x - m_size.y, m_size.y };

	// 矩形の描画
	int color = (m_changed ? 0x00d14d : 0xAAAAAA);

	DrawBoxAA(m_position.x - rectSize.x / 2, m_position.y - rectSize.y / 2, m_position.x + rectSize.x / 2 + 1, m_position.y + rectSize.y / 2 + 1, color, true);

	// 円の描画
	DrawCircleAA(circlePos1.x, circlePos1.y, m_size.y / 2, 32, color, true);
	DrawCircleAA(circlePos2.x, circlePos2.y, m_size.y / 2, 32, color, true);

	// カーソルの描画
	switch (m_nowState)
	{
	case Switch::State::On:
		DrawCircleAA(circlePos2.x, circlePos2.y, (m_size.y / 2) * (0.8), 32, 0x333333, true);
		break;
	case Switch::State::Off:
		DrawCircleAA(circlePos1.x, circlePos1.y, (m_size.y / 2) * (0.8), 32, 0x333333, true);
		break;
	case Switch::State::ToOn:
		DrawCircleAA(circlePos1.x + Easing::EaseInOutQuad(m_easingX) * (circlePos2.x - circlePos1.x), circlePos1.y, (m_size.y / 2) * (0.8), 32, 0x333333, true);
		break;
	case Switch::State::ToOff:
		DrawCircleAA(circlePos2.x - Easing::EaseOutQuad(m_easingX) * (circlePos2.x - circlePos1.x), circlePos1.y, (m_size.y / 2) * (0.8), 32, 0x333333, true);
		break;
	default:
		break;
	}
}

bool Switch::OnMe(Vector2D pos)
{
	bool onRect = (pos.x <= m_position.x + (m_size.x / 2 - m_size.y / 2) && pos.x >= m_position.x - (m_size.x / 2 - m_size.y / 2)) && (pos.y <= m_position.y + m_size.y / 2 && pos.y >= m_position.y - m_size.y / 2);
	bool onCircle1 = (GetLength(pos, Vector2D{ m_position.x - m_size.x / 2 + m_size.y / 2, m_position.y }) <= m_size.y / 2);
	bool onCircle2 = (GetLength(pos, Vector2D{ m_position.x + m_size.x / 2 - m_size.y / 2, m_position.y }) <= m_size.y / 2);

	return onRect || onCircle1 || onCircle2;
}
