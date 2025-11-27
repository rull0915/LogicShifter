#include "Game.h"

Game::Game()
	: m_key{}, m_oldKey{}
{
	// 絵の読み込み
	LoadGraphics();

	// キーの追加
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_11, KEY_INPUT_RETURN);
	SetJoypadInputToKeyInput(DX_INPUT_PAD1, PAD_INPUT_12, KEY_INPUT_R);
}

Game::~Game()
{
}

void Game::Initialize()
{
	// シーンの登録
	m_sceneManager.RegisterScene("GamePlay", std::make_unique<GamePlayScene>(this));

	// 開始時のシーンをタイトルに設定
	m_sceneManager.SetStartScene("GamePlay");
}

void Game::Update(float elapsedTime)
{
	// キー情報の取得
	m_oldKey = m_key;
	m_key = GetJoypadInputState(DX_INPUT_KEY);

	MouseUpdate();

	// リクエストがあればシーンを切り替える
	m_sceneManager.Update(elapsedTime);
}

void Game::Render()
{
	// 現在のシーンの描画
	m_sceneManager.Render();
}
