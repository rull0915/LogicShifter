#include "ModeSelectScene.h"
#include "../Game.h"

ModeSelectScene::ModeSelectScene(Game* pGame)
	: Scene(pGame->GetSceneManager())
	, m_pGame{ pGame }
	, m_buttons{}
	, m_particle{}
	, m_titleButton{ { Screen::WIDTH / 3, Screen::HEIGHT * (11.0f / 12)}, { Screen::WIDTH / 5, Screen::HEIGHT / 16}, false, 0xAAAAAA, true }
	, m_exitButton{ { Screen::WIDTH * (2.0f / 3), Screen::HEIGHT * (11.0f / 12)}, {Screen::WIDTH / 5, Screen::HEIGHT / 16}, false, 0xAAAAAA, true}
{
	m_buttons.clear();

	m_buttons[PlayMode::Stage] = std::make_unique<Button>(Vector2D{ Screen::WIDTH * (2.f / 10), Screen::HEIGHT * (8.f / 16) }, Vector2D{ 313, 455 }, true, m_ghIcons["StageMode"]);
	m_buttons[PlayMode::Free]  = std::make_unique<Button>(Vector2D{ Screen::WIDTH * (5.f / 10), Screen::HEIGHT * (8.f / 16) }, Vector2D{ 313, 455 }, true, m_ghIcons["FreeMode"]);
	m_buttons[PlayMode::Edit]  = std::make_unique<Button>(Vector2D{ Screen::WIDTH * (8.f / 10), Screen::HEIGHT * (8.f / 16) }, Vector2D{ 313, 455 }, true, m_ghIcons["EditMode"]);
}

void ModeSelectScene::Initialize()
{
	m_particle.Initialize(ShapeType::Block, 0.1f, { {0, Screen::HEIGHT / 2},{Screen::WIDTH, Screen::HEIGHT * 1.5} }, { {40, 40},{60, 60} } );

	m_titleButton.Initialize();
	m_exitButton.Initialize();

	Sound::FadeIn(Sound::Type::SelectBgm, 0.5f);
}

void ModeSelectScene::Update(float elapsedTime)
{
	for (auto& button : m_buttons)
	{
		button.second->Update();

		if(button.second->GetIsPressed())
		{
			m_pGame->SetPlayMode(button.first);

			// ステージモードなら
			if (button.first == PlayMode::Stage)
			{
				// セレクトに移行
				ChangeScene("Select",
					std::make_unique<FadeTransition>(0.3f, Transition::Mode::In, 0x000000),
					std::make_unique<FadeTransition>(0.3f, Transition::Mode::Out, 0x000000)
					);
			}

			// それ以外なら
			else
			{
				// ゲームプレイに移行
				ChangeScene("GamePlay",
					std::make_unique<FadeTransition>(0.3f, Transition::Mode::In, 0x000000),
					std::make_unique<FadeTransition>(0.3f, Transition::Mode::Out, 0x000000)
					);
			}
		}
	}

	m_particle.Update(elapsedTime);

	m_titleButton.Update();
	m_exitButton.Update();

	if(m_titleButton.GetIsPressed())
	{
		// タイトルに移行
		ChangeScene("Title",
			std::make_unique<IrisTransition>(1.0f, Transition::Mode::In, 0x888888),
			std::make_unique<IrisTransition>(1.0f, Transition::Mode::Out, 0x888888)
		);
	}

	if(m_exitButton.GetIsPressed())
	{
		m_pGame->End();
	}
}

void ModeSelectScene::Render()
{
	m_particle.Render(0x444444);

	for (auto&button : m_buttons) button.second->Render();

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (2.f / 4), Screen::HEIGHT * (1.f / 12), 0xFFFFFF, GetFontHandle(80), L"ModeSelect");

	m_titleButton.Render();
	m_exitButton.Render();

	MyDrawFormatStringToHandleToCenter(m_titleButton.GetPos().x, m_titleButton.GetPos().y, 0x000000, GetFontHandle(24), L"Title");
	MyDrawFormatStringToHandleToCenter(m_exitButton.GetPos().x, m_exitButton.GetPos().y, 0x000000, GetFontHandle(24), L"Exit");
}

void ModeSelectScene::Finalize()
{
	for (auto& button : m_buttons) button.second->Finalize();

	m_titleButton.Finalize();
	m_exitButton.Finalize();

	Sound::FadeOut(Sound::Type::SelectBgm, 0.5f);
}
