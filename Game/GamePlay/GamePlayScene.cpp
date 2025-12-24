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
	m_logic.SetFileName(m_pGame->GetStageFileName());

	m_logic.Initialize(m_pGame->GetPlayMode());

	// bgmの再生
	Sound::FadeIn(Sound::Type::GamePlayBgm, 0.5f);
}

// 更新関数 
void GamePlayScene::Update(float elapsedTime)
{
	// 論理回路の更新
	m_logic.Update(elapsedTime);

	if (m_logic.ToResult())
	{
		ChangeScene("Result",
			std::make_unique<FadeTransition>(0.5f, Transition::Mode::In, 0x000000),
			std::make_unique<FadeTransition>(0.5f, Transition::Mode::Out, 0x000000)
		);
	}
}

// 描画関数
void GamePlayScene::Render()
{
	m_logic.Render();
}

// 終了関数
void GamePlayScene::Finalize()
{
	m_logic.Finalize();

	// bgmの停止
	Sound::FadeOut(Sound::Type::GamePlayBgm, 0.5f);
}
