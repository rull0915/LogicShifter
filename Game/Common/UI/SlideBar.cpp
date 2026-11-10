#include "SlideBar.h"

SlideBar::SlideBar(float width, Vector2D pos, float radius , int barColor, int buttonColor)
	: m_barWidth{ width }
	, m_barCenterPos{ pos }
	, m_buttonCenterPos{ pos.x, pos.y }
	, m_buttonRadius{ radius }
	, m_barColor{ barColor }
	, m_buttonColor{ buttonColor }
	, m_isMoving{ false }
{
}

void SlideBar::Initialize()
{
	// ボタンの位置の初期化
	m_buttonCenterPos = { m_barCenterPos.x, m_barCenterPos.y };

	// フラグの初期化
	m_isMoving = false;
}

void SlideBar::Update()
{
	// マウスが左クリックされたら
	if(MouseDown() & MOUSE_INPUT_LEFT)
	{
		// マウス座標がボタン上なら
		if (GetLength({ (float)m_mousePos.x, (float)m_mousePos.y }, m_buttonCenterPos) <= m_buttonRadius)
		{
			// 移動中フラグをオンに
			m_isMoving = true;
		}
	}

	// マウスが離されたら
	if(MouseUp() & MOUSE_INPUT_LEFT)
	{
		// 移動中フラグをオフに
		m_isMoving = false;
	}

	// 移動中なら
	if(m_isMoving)
	{
		// ボタンのX座標をマウスに合わせる
		m_buttonCenterPos.x = static_cast<float>(m_mousePos.x);

		// バーからはみ出したら補正
		if (m_buttonCenterPos.x < m_barCenterPos.x - m_barWidth / 2) m_buttonCenterPos.x = m_barCenterPos.x - m_barWidth / 2;
		if (m_buttonCenterPos.x > m_barCenterPos.x + m_barWidth / 2) m_buttonCenterPos.x = m_barCenterPos.x + m_barWidth / 2;
	}
}

void SlideBar::Render()
{
	// バーの描画
	DrawLineAA(
		m_barCenterPos.x - m_barWidth / 2, m_barCenterPos.y,
		m_barCenterPos.x + m_barWidth / 2, m_barCenterPos.y,
		m_barColor, m_buttonRadius / 2
	);

	// ボタンの描画
	DrawCircleAA(m_buttonCenterPos.x, m_buttonCenterPos.y, m_buttonRadius, 16, m_buttonColor, true);

	// 移動中なら
	if(m_isMoving)
	{
		// 少し黒く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
		DrawCircleAA(m_buttonCenterPos.x, m_buttonCenterPos.y, m_buttonRadius, 16, 0x000000, true);
	}
	// 移動中ではなく、カーソルがボタン上にあれば
	else if(GetLength({ (float)m_mousePos.x, (float)m_mousePos.y }, m_buttonCenterPos) <= m_buttonRadius)
	{
		// 少し白く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
		DrawCircleAA(m_buttonCenterPos.x, m_buttonCenterPos.y, m_buttonRadius, 16, 0xffffff, true);
	}

	// 描画モードのリセット
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SlideBar::Finalize()
{
}

float SlideBar::GetResult()
{
	float pos = m_buttonCenterPos.x - (m_barCenterPos.x - m_barWidth / 2);

	return pos / m_barWidth;
}

void SlideBar::SetResult(float val)
{
	m_buttonCenterPos.x = (m_barCenterPos.x - m_barWidth / 2) + val * m_barWidth;
}
