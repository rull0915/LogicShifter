#include "TextBox.h"

void TextBox::Update(bool isActive, Vector2D pos, const std::wstring& str)
{
	m_isActive = isActive;
	m_position = pos;
	m_str = str;
}

void TextBox::Render(bool mode)
{
	if (!m_isActive) return;

	// s”‚ğæ“¾
	int lineNum = 1;
	int fontSize = 24;

	for(int i = 0; i < m_str.size(); i++)
	{
		if (m_str[i] == '\n') lineNum++;
	}

	int len = GetDrawFormatStringWidthToHandle(GetFontHandle(fontSize), m_str.c_str());

	if(mode)
	{
		DrawBox(m_position.x, m_position.y, m_position.x + len, m_position.y + fontSize * lineNum, 0xAAAAAA, true);

		if (m_isActive)
		{
			DrawFormatStringToHandle(m_position.x, m_position.y, 0x222222, GetFontHandle(fontSize), m_str.c_str());
		}
	}
	else 
	{
		DrawBox(m_position.x - len, m_position.y, m_position.x, m_position.y + fontSize * lineNum, 0xAAAAAA, true);

		if (m_isActive)
		{
			DrawFormatStringToHandle(m_position.x - len, m_position.y, 0x222222, GetFontHandle(fontSize), m_str.c_str());
		}
	}
}
