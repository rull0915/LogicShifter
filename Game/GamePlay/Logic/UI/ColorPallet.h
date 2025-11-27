#pragma once
#include "Button.h"

class ColorPallet
{
public:
	// サイズ
	static constexpr Vector2DInt SIZE = { 312, 390 };

private:

	// 配置位置
	std::unordered_map<std::string, Vector2D> PUT_POS =
	{
		{"SQUARE_LEFTUP",		{ SIZE.x * (1.0f / 16), SIZE.y * (5.0f / 32)}},
		{"SQUARE_RIGHTDOWN",	{ SIZE.x * (12.0f / 16), SIZE.y * (5.0f / 32) + SIZE.x * (11.0f / 16) }},
		{ "COLOR_LEFTUP",		{ SIZE.x * (13.0f / 16), SIZE.y * (5.0f / 32) } },
		{ "COLOR_RIGHTDOWN",	{ SIZE.x * (15.0f / 16), SIZE.y * (5.0f / 32) + SIZE.x * (11.0f / 16) } },
		{ "BOX_LEFTUP",			{ SIZE.x * (1.0f / 16),  SIZE.y * (24.0f / 32) }},
		{ "BOX_RIGHTDOWN",		{ SIZE.x * (15.0f / 16), SIZE.y * (53.0f / 64) }},
		{ "CHECK_BUTTON",		{ SIZE.x * (22.0f / 32), SIZE.y * (59.0f / 64) }},
		{ "CANCEL_BUTTON",		{ SIZE.x * (14.0f / 16), SIZE.y * (59.0f / 64) }},
	};

private:
	// 位置
	Vector2D m_position;

	// HSV
	int m_h, m_s, m_v;

	// 明度彩度用の画像
	int m_screenSV;
	// 色相用の画像
	int m_screenH;

	// 色変更中の変数へのポインタ
	int* m_changeColor;

	// 開始時の色
	int m_startColor;

	// アクティブフラグ
	bool m_isActive;

	// ボタン
	Button m_checkButton;
	Button m_cancelButton;

public:
	ColorPallet();

	void Initialize(Vector2D pos, int* color);

	void Update();
	void Render();

	bool GetIsActive() const { return m_isActive; }

	// 指定した位置が自分の上にあるかを返す関数
	bool GetMouseOnThis(Vector2DInt screenPos)
	{
		return m_isActive && ((screenPos.x > m_position.x && screenPos.x < m_position.x + SIZE.x) &&
			(screenPos.y > m_position.y && screenPos.y < m_position.y + SIZE.y));
	}
};

