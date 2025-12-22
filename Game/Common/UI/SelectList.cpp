#include "SelectList.h"

SelectList::SelectList(Vector2D pos, Vector2D size)
	: m_position{ pos }
	, m_aChouiceSize{ size }
	, m_choices{}
	, m_standardButton{ pos, size, false, 0xBBBBBB, false }
	, m_choiceButtons{}
	, m_isOpen{ false }
	, m_choiced{}
	, m_choicedIndex{ 0 }
{
}

void SelectList::Initialize()
{
	m_standardButton.Initialize();
}

void SelectList::Update() 
{
	if(m_isOpen)
	{
		m_standardButton.ChengePos(m_position + Vector2D{ 0, -m_choicedIndex * m_aChouiceSize.y });

		for(int i = 0; i < m_choices.size(); i++)
		{
			auto& choice = m_choiceButtons[m_choices[i]];

			// 位置の変更
			choice->ChengePos(m_standardButton.GetPos() + Vector2D{0, m_aChouiceSize.y * (i + 1)});

			choice->Update();

			if (choice->GetIsPressed())
			{
				// 選択
				m_choiced = m_choices[i];
				m_choicedIndex = i + 1;

				m_isOpen = false;
			}
		}
	}
	else 
	{
		m_standardButton.ChengePos(m_position);
	}

	m_standardButton.Update();

	if (m_standardButton.GetIsPressed()) 
	{
		if(m_isOpen)
		{
			m_choiced = L"";
			m_choicedIndex = 0;
		}

		m_isOpen = !m_isOpen;
	}
}

void SelectList::Render()
{
	m_standardButton.Render();
	if(m_choicedIndex == 0 || m_isOpen) MyDrawFormatStringToHandleToCenter(m_standardButton.GetPos().x, m_standardButton.GetPos().y, 0x000000, GetFontHandle(m_aChouiceSize.y / 2), L"選択");
	else MyDrawFormatStringToHandleToCenter(m_standardButton.GetPos().x, m_standardButton.GetPos().y, 0x000000, GetFontHandle(m_aChouiceSize.y / 2), m_choiced.c_str());

	if(m_isOpen)
	{
		for (auto& button : m_choiceButtons)
		{
			button.second->Render();

			MyDrawFormatStringToHandleToCenter(button.second->GetPos().x, button.second->GetPos().y, 0x000000, GetFontHandle(m_aChouiceSize.y / 2), button.first.c_str());
		}

		if (m_choicedIndex != 0) 
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
			DrawBox(m_position.x - m_aChouiceSize.x / 2, m_position.y - m_aChouiceSize.y / 2, m_position.x + m_aChouiceSize.x / 2, m_position.y + m_aChouiceSize.y / 2, 0xAAAAFF, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		DrawLine(
			m_standardButton.GetPos().x - m_aChouiceSize.x / 2, m_standardButton.GetPos().y + m_aChouiceSize.y / 2,
			m_standardButton.GetPos().x + m_aChouiceSize.x / 2, m_standardButton.GetPos().y + m_aChouiceSize.y / 2,
			0x444444
		);
	}
}

void SelectList::AddChoice(std::wstring choice)
{
	// もしまだ存在しない選択肢なら
	if(m_choiceButtons.find(choice) == m_choiceButtons.end())
	{
		// 選択肢を追加
		m_choices.push_back(choice);

		// 選択ボタンを追加
		m_choiceButtons[choice] = std::make_unique<Button>(m_position, m_aChouiceSize, false, 0xBBBBBB, false);
	}
}

void SelectList::DeleteChoice(std::wstring choice)
{
	// 存在する選択肢なら
	if (m_choiceButtons.find(choice) != m_choiceButtons.end())
	{
		// 削除
		for(int i = 0; i < m_choices.size(); i++)
		{
			if(m_choices[i] == choice)
			{
				m_choices.erase(m_choices.begin() + i);
				break;
			}
		}

		m_choiceButtons.erase(choice);
	}
}

std::wstring SelectList::GetChoiced()
{
	return m_choiced;
}

bool SelectList::GetIsOpen()
{
	return m_isOpen;
}
