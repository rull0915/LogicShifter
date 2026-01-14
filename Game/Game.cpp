#include "Game.h"
#include "../Game/Common/ThreadPool.h"

Game::Game()
	: m_key{}, m_oldKey{}
	, m_stageFileName{}
	, m_playMode{ PlayMode::Edit }
	, m_pause{ this }
	, m_pauseButton{ Vector2D{ 100, Screen::HEIGHT - 50 }, Vector2D{ 150, 50 }, false, 0xBBBBBB, true}
	, m_endFrag{ false }
	, m_isPressed{}
{
	// キーの追加
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_11, KEY_INPUT_RETURN);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_12, KEY_INPUT_R);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_13, KEY_INPUT_ESCAPE);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_14, KEY_INPUT_C);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_15, KEY_INPUT_U);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_16, KEY_INPUT_S);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_17, KEY_INPUT_H);
}

Game::~Game()
{
}

void Game::Initialize()
{
	// シーンの登録
	m_sceneManager.RegisterScene("GamePlay",	std::make_unique<GamePlayScene>(this));
	m_sceneManager.RegisterScene("Select",		std::make_unique<SelectScene>(this));
	m_sceneManager.RegisterScene("ModeSelect",	std::make_unique<ModeSelectScene>(this));
	m_sceneManager.RegisterScene("Title",		std::make_unique<TitleScene>(this));
	m_sceneManager.RegisterScene("Result",		std::make_unique<ResultScene>(this));

	// 開始時のシーンをタイトルに設定
	m_sceneManager.SetStartScene("Title");
}

void Game::Update(float elapsedTime)
{
	// キー情報の取得
	m_oldKey = m_key;
	m_key = GetJoypadInputState(DX_INPUT_KEY);

	m_mouseDrawMode = MouseMode::Normal;

	MouseUpdate();

	Sound::Update(elapsedTime);

	m_pauseButton.Update();

	if(m_pauseButton.GetIsPressed()) 
	{
		if(m_pause.GetIsActive())
		{
			m_pause.SetIsActive(false);
		}
		else 
		{
			if (m_sceneManager.GetSceneName() == "Select")
			{
				m_pause.Initialize(Pause::State::StageSelect);
			}
			else if (m_sceneManager.GetSceneName() == "GamePlay" && m_playMode == PlayMode::Stage)
			{
				m_pause.Initialize(Pause::State::StageMode);
			}
			else if (m_sceneManager.GetSceneName() == "GamePlay" && m_playMode != PlayMode::Stage)
			{
				m_pause.Initialize(Pause::State::OtherMode);
			}
			else
			{
				m_pause.Initialize(Pause::State::Others);
			}
		}
	}

	// リクエストがあればシーンを切り替える
	if (!m_pause.GetIsActive()) m_sceneManager.Update(elapsedTime);

	m_pause.Update(elapsedTime);

	// 隠しコマンド
	if(GetKeyTrigger() & PAD_INPUT_14) m_isPressed[0] = true;
	if(GetKeyTrigger() & PAD_INPUT_12) m_isPressed[1] = true;
	if(GetKeyTrigger() & PAD_INPUT_15) m_isPressed[2] = true;
	if(GetKeyTrigger() & PAD_INPUT_16) m_isPressed[3] = true;
	if(GetKeyTrigger() & PAD_INPUT_17) m_isPressed[4] = true;

	if((m_isPressed[0] && (m_isPressed[1] && m_isPressed[2])) && (m_isPressed[3] && m_isPressed[4]))
	{
		Sound::Play(Sound::Type::Crush, DX_PLAYTYPE_BACK);

		for (bool& t : m_isPressed) t = false;
	}
}

void Game::Render()
{
	// 現在のシーンの描画
	m_sceneManager.Render();

	m_pause.Render();

	//if (m_sceneManager.GetSceneName() == "Select" || m_sceneManager.GetSceneName() == "GamePlay")
	{
		m_pauseButton.Render();

		MyDrawFormatStringToHandleToCenter(m_pauseButton.GetPos().x, m_pauseButton.GetPos().y, 0x000000, GetFontHandle(32), L"Pause");
	}

	m_sceneManager.TransitionRender();

	MouseRender();
}

void Game::End()
{
	m_endFrag = true;
}
