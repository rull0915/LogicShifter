#include "Game.h"

Game::Game()
	: m_key{}, m_oldKey{}
	, m_stageFileName{}
	, m_playMode{ PlayMode::Edit }
	, m_pause{ this }
	, m_pauseButton{ Vector2D{ 100, Screen::HEIGHT - 50 }, Vector2D{ 150, 50 }, false, 0xBBBBBB, true}
	, m_endFrag{ false }
{
	// 絵の読み込み
	LoadGraphics();

	// キーの追加
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_11, KEY_INPUT_RETURN);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_12, KEY_INPUT_R);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_13, KEY_INPUT_ESCAPE);
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

	m_pause.Initialize();
}

void Game::Update(float elapsedTime)
{
	// キー情報の取得
	m_oldKey = m_key;
	m_key = GetJoypadInputState(DX_INPUT_KEY);

	m_mouseDrawMode = MouseMode::Normal;

	MouseUpdate();

	if (m_sceneManager.GetSceneName() == "Select" || m_sceneManager.GetSceneName() == "GamePlay") m_pauseButton.Update();

	if(m_pauseButton.GetIsPressed()) 
	{
		if(m_sceneManager.GetSceneName() == "Select")
		{
			m_pause.Initialize(Pause::State::StageSelect);
		}
		if (m_sceneManager.GetSceneName() == "GamePlay" && m_playMode == PlayMode::Stage)
		{
			m_pause.Initialize(Pause::State::StageMode);
		}
		if (m_sceneManager.GetSceneName() == "GamePlay" && m_playMode != PlayMode::Stage)
		{
			m_pause.Initialize(Pause::State::OtherMode);
		}
	}

	// リクエストがあればシーンを切り替える
	if (!m_pause.GetIsActive()) m_sceneManager.Update(elapsedTime);

	m_pause.Update(elapsedTime);
}

void Game::Render()
{
	// 現在のシーンの描画
	m_sceneManager.Render();

	m_pause.Render();

	if (m_sceneManager.GetSceneName() == "Select" || m_sceneManager.GetSceneName() == "GamePlay")
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
