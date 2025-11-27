#include "ModeSelect.h"
#include "Logic/LogicCircuit.h"

ModeSelect::ModeSelect(LogicCircuit* parent)
	: m_pParent{ parent }
	, m_buttons{}
{
	m_buttons.clear();

	m_buttons[PlayMode::Edit]  = std::make_unique<Button>(Vector2D{ Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (7.f / 16) }, Vector2D{ Screen::WIDTH * (1.f / 2), Screen::HEIGHT * (1.f / 8) }, false, 0xAAAAAA);
	m_buttons[PlayMode::Free]  = std::make_unique<Button>(Vector2D{ Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (10.f / 16) }, Vector2D{ Screen::WIDTH * (1.f / 2), Screen::HEIGHT * (1.f / 8) }, false, 0xAAAAAA);
	m_buttons[PlayMode::Stage] = std::make_unique<Button>(Vector2D{ Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (13.f / 16) }, Vector2D{ Screen::WIDTH * (1.f / 2), Screen::HEIGHT * (1.f / 8) }, false, 0xAAAAAA);
}

void ModeSelect::Initialize()
{
}

void ModeSelect::Update(float elapsedTime)
{
	for (auto& button : m_buttons)
	{
		button.second->Update();

		if(button.second->GetIsPressed())
		{
			m_pParent->Initialize(button.first);
		}
	}
}

void ModeSelect::Render()
{
	for (auto&button : m_buttons) button.second->Render();

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (7.f / 16), 0x222222, GetFontHandle(48), L"EditMode");
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (10.f / 16), 0x222222, GetFontHandle(48), L"FreeMode");
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (13.f / 16), 0x222222, GetFontHandle(48), L"StageMode");

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (1.f / 8), 0xFFFFFF, GetFontHandle(80), L"ModeSelect");
}
