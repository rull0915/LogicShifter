#pragma once

// シーン
#include "GamePlay/GamePlayScene.h"

#include "Common/SceneManager.h"

class Game
{
	// 変数宣言 ---------------------------------------
private:

	int m_key;
	int m_oldKey;

	// シーン関連
	SceneManager m_sceneManager;

public:
	// 関数宣言 ----------------------------------------

	// コンストラクタ / デストラクタ
	Game();
	~Game();

	// 初期化関数
	void Initialize();

	// 更新関数
	void Update(float elapsedTime);

	// 描画関数
	void Render();

	// シーンマネージャーを返す関数
	SceneManager* GetSceneManager() { return &m_sceneManager; }

	// キー情報を返す関数
	int GetKeyTrigger() const { return (~m_oldKey & m_key); }
	int GetKeyCondition() const { return (m_key); }
};