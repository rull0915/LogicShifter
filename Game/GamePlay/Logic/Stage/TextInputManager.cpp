#include "TextInputManager.h"

TextInputManager::TextInputManager(std::wstring* change, Vector2D pos, Vector2D size)
	: m_changeString{ change }
	, m_position{ pos }
	, m_size{ size }
	, m_keyInputHandle{ -1 }
	, result{}
	, m_isStart{ false }
{
}

void TextInputManager::Initialize(bool numOnly)
{
	// キー入力ハンドルの作成
	if(m_keyInputHandle == -1) m_keyInputHandle = MakeKeyInput(255, false, false, numOnly);
}

void TextInputManager::Update()
{
	// クリックされたら
	if (MouseDown() & MOUSE_INPUT_LEFT)
	{
		// マウスがボックス上にあれば
		if (OnMe({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) }))
		{
			// 入力開始
			SetActiveKeyInput(m_keyInputHandle);

			m_isStart = true;
		}
	}

	// 入力が終了していたら
	if(CheckKeyInput(m_keyInputHandle) != 0)
	{
		// 文字列を格納
		GetKeyInputString(result, m_keyInputHandle);

		*m_changeString = result;
	}
}

void TextInputManager::Render()
{
	DrawBox(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2, m_position.x + m_size.x / 2, m_position.y + m_size.y / 2, 0xBBBBBB, true);

	// キー入力中なら
	if (CheckKeyInput(m_keyInputHandle) == 0) 
	{
		// 入力時のフォントを変更する
		SetKeyInputStringFont(GetFontHandle(static_cast<int>(m_size.y * (1.0f / 2))));
		SetKeyInputStringColor2(DX_KEYINPSTRCOLOR_NORMAL_STR, 0x444444);

		TCHAR test[255];
		GetKeyInputString(test, m_keyInputHandle);
		int width = GetDrawFormatStringWidthToHandle(GetFontHandle(m_size.y / 2), test);

		// 入力中の文字列を描画する
		DrawKeyInputString(m_position.x - width / 2, m_position.y - m_size.y / 4, m_keyInputHandle);
	}
	else
	{
		int width = GetDrawFormatStringWidthToHandle(GetFontHandle(m_size.y / 2), m_changeString->c_str());
		DrawFormatStringToHandle(m_position.x - width / 2, m_position.y - m_size.y / 4, 0, GetFontHandle(m_size.y / 2), m_changeString->c_str());
	}

}

bool TextInputManager::OnMe(Vector2D pos)
{
	return (
		(pos.x >= m_position.x - m_size.x / 2 &&
			pos.x <= m_position.x + m_size.x / 2) &&
		(pos.y >= m_position.y - m_size.y / 2 &&
			pos.y <= m_position.y + m_size.y / 2)
		);
}
