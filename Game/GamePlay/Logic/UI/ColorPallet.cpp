#include "ColorPallet.h"

ColorPallet::ColorPallet()
	: m_h{ 0 }
	, m_s{ 0 }
	, m_v{ 0 }
	, m_changeColor{ nullptr }
	, m_isActive{ false }
	, m_checkButton{ m_position + PUT_POS["CHECK_BUTTON"], {SIZE.x / 7, SIZE.x / 7}, true, m_ghIcons["Check"]}
	, m_cancelButton{ m_position + PUT_POS["CANCEL_BUTTON"], {SIZE.x / 7, SIZE.x / 7}, true, m_ghIcons["Cancel"]}
	, m_startColor{ 0 }
{
	m_screenSV = MakeScreen(255, 255, true);

	m_screenH = MakeScreen(1, 360, true);

	SetDrawScreen(m_screenH);

	for (int i = 0; i < 360; i++)
	{
		DrawPixel(0, i, HSVToRGB(i, 255, 255));
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void ColorPallet::Initialize(Vector2D pos, int* color)
{
	m_changeColor = color;

	// RGBからHSVを取得
	RGBToHSV(*m_changeColor, m_h, m_s, m_v);
	
	m_startColor = *m_changeColor;

	// 位置をセット
	m_position = pos;

	// アクティブに
	m_isActive = true;

	// ボタンの位置の更新
	m_checkButton.ChengePos(m_position + PUT_POS["CHECK_BUTTON"]);
	m_cancelButton.ChengePos(m_position + PUT_POS["CANCEL_BUTTON"]);
}

void ColorPallet::Update()
{
	// 非アクティブならスキップ
	if (!m_isActive) return;

	// 左クリックされたとき
	if (MouseDown() & MOUSE_INPUT_LEFT)
	{
		// マウスが明度彩度内にあれば
		if ((m_mousePos.x > m_position.x + PUT_POS["SQUARE_LEFTUP"].x && m_mousePos.y > m_position.y + PUT_POS["SQUARE_LEFTUP"].y) &&
			(m_mousePos.x < m_position.x + PUT_POS["SQUARE_RIGHTDOWN"].x && m_mousePos.y < m_position.y + PUT_POS["SQUARE_RIGHTDOWN"].y))
		{
			// 彩度明度の更新
			m_s = (m_mousePos.x - (m_position.x + PUT_POS["SQUARE_LEFTUP"].x)) / (PUT_POS["SQUARE_RIGHTDOWN"].x - PUT_POS["SQUARE_LEFTUP"].x) * 255;
			m_v = (1.f - (m_mousePos.y - (m_position.y + PUT_POS["SQUARE_LEFTUP"].y)) / (PUT_POS["SQUARE_RIGHTDOWN"].y - PUT_POS["SQUARE_LEFTUP"].y)) * 255;
		}

		// マウスが色相内にあれば
		if ((m_mousePos.x > m_position.x + PUT_POS["COLOR_LEFTUP"].x && m_mousePos.y > m_position.y + PUT_POS["COLOR_LEFTUP"].y) &&
			(m_mousePos.x < m_position.x + PUT_POS["COLOR_RIGHTDOWN"].x && m_mousePos.y < m_position.y + PUT_POS["COLOR_RIGHTDOWN"].y))
		{
			// 色相の更新
			m_h = (m_mousePos.y - (m_position.y + PUT_POS["COLOR_LEFTUP"].y)) / (PUT_POS["COLOR_RIGHTDOWN"].y - PUT_POS["COLOR_LEFTUP"].y) * 360;
		}
	}

	// 色の変更
	*m_changeColor = HSVToRGB(m_h, m_s, m_v);

	// チェックボタン
	m_checkButton.Update();
	// キャンセルボタン
	m_cancelButton.Update();

	if(m_checkButton.GetIsPressed()) 
	{
		m_isActive = false;
		m_changeColor = nullptr;
	}

	else if(m_cancelButton.GetIsPressed())
	{
		*m_changeColor = m_startColor;
		m_isActive = false;
		m_changeColor = nullptr;
	}

	// 自分の外側をクリックされたら終了
	else if((MouseDown() & MOUSE_INPUT_LEFT) && !GetMouseOnThis(m_mousePos))
	{
		*m_changeColor = m_startColor;
		m_isActive = false;
		m_changeColor = nullptr;
	}
}

void ColorPallet::Render()
{
	// 非アクティブならスキップ
	if (!m_isActive) return;

	// 彩度用のスクリーン
	SetDrawScreen(m_screenSV);

	// 彩度明度の描画
	// 明度
	for (int i = 0; i <= 255; i++)
	{
		// 彩度
		for (int j = 0; j <= 255; j++)
		{
			DrawPixel(j, i, HSVToRGB(m_h, j, 255 - i));
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// 画面への描画
	// 枠の描画
	DrawBox(m_position.x, m_position.y, m_position.x + SIZE.x, m_position.y + SIZE.y, 0x333233, true);

	// タイトルの描画
//	DrawFormatStringToHandle(m_position.x + (SIZE.x * (1.f / 16)), m_position.y + SIZE.y * (1.f / 80), 0xffffff, GetFontHandle(SIZE.y / 10), L"ChooseColor");

	// 枠の描画
	DrawBox(m_position.x, m_position.y + (SIZE.y * (3.0f / 32)), m_position.x + SIZE.x, m_position.y + SIZE.y, 0x474747, true);

	// 彩度 明度の描画
	DrawExtendGraph(m_position.x + PUT_POS["SQUARE_LEFTUP"].x, m_position.y + PUT_POS["SQUARE_LEFTUP"].y,
		m_position.x + PUT_POS["SQUARE_RIGHTDOWN"].x, m_position.y + PUT_POS["SQUARE_RIGHTDOWN"].y,
		m_screenSV, true);

	// 色相の描画
	DrawExtendGraph(m_position.x + PUT_POS["COLOR_LEFTUP"].x, m_position.y + PUT_POS["COLOR_LEFTUP"].y,
		m_position.x + PUT_POS["COLOR_RIGHTDOWN"].x, m_position.y + PUT_POS["COLOR_RIGHTDOWN"].y,
		m_screenH, true);

	// 現在の色の描画
	DrawBox(m_position.x + PUT_POS["BOX_LEFTUP"].x, m_position.y + PUT_POS["BOX_LEFTUP"].y,
		m_position.x + PUT_POS["BOX_RIGHTDOWN"].x, m_position.y + PUT_POS["BOX_RIGHTDOWN"].y,
		HSVToRGB(m_h, m_s, m_v), true);

	// 彩度明度ポインタの描画
	int x = m_position.x + PUT_POS["SQUARE_LEFTUP"].x + (m_s * ((PUT_POS["SQUARE_RIGHTDOWN"].x - PUT_POS["SQUARE_LEFTUP"].x) / 255));
	int y = m_position.y + PUT_POS["SQUARE_LEFTUP"].y + ((255 - m_v) * ((PUT_POS["SQUARE_RIGHTDOWN"].y - PUT_POS["SQUARE_LEFTUP"].y) / 255));

	DrawCircleAA(x, y, 5, 10, 0xffffff, true);
	DrawCircleAA(x, y, 5, 10, 0x000000, false);

	// 色相バーの描画
	int yy = m_position.y + PUT_POS["COLOR_LEFTUP"].y + (m_h * ((PUT_POS["COLOR_RIGHTDOWN"].y - PUT_POS["COLOR_LEFTUP"].y) / 360));

	DrawBoxAA(m_position.x + PUT_POS["COLOR_LEFTUP"].x - 3, yy - 3, m_position.x + PUT_POS["COLOR_RIGHTDOWN"].x + 3, yy + 3, 0xffffff, true);
	DrawBoxAA(m_position.x + PUT_POS["COLOR_LEFTUP"].x - 3, yy - 3, m_position.x + PUT_POS["COLOR_RIGHTDOWN"].x + 3, yy + 3, 0x000000, false);

	// ボタンの描画
	m_checkButton.Render();
	m_cancelButton.Render();
}
