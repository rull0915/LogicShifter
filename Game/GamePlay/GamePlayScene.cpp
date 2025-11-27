#include "GamePlayScene.h"
#include "../Game.h"

// コンストラクタ
GamePlayScene::GamePlayScene(Game* pGame)
	: Scene(pGame->GetSceneManager())
	, m_pGame{ pGame }
	, m_logic{}
{
}

GamePlayScene::~GamePlayScene()
{
}

// 初期化関数
void GamePlayScene::Initialize()
{
	m_logic.Initialize(PlayMode::Select);
}

// 更新関数 
void GamePlayScene::Update(float elapsedTime)
{
	// 論理回路の更新
	m_logic.Update(elapsedTime);
}

// 描画関数
void GamePlayScene::Render()
{
	m_logic.Render();
}

// 終了関数
void GamePlayScene::Finalize()
{
}
