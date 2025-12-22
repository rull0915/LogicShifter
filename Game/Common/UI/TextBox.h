#pragma once

class TextBox
{
	// ----------- メンバ変数宣言 --------------
	// 位置
	Vector2D m_position;

	std::wstring m_str;

	bool m_isActive;

	// 関数宣言
public:
	// 更新
	void Update(bool isActive, Vector2D pos, const std::wstring& str);

	// 描画
	void Render(bool mode);
};

