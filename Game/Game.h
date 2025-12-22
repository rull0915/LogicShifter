#pragma once

// シーン
#include "GamePlay/GamePlayScene.h"
#include "Select/SelectScene.h"
#include "ModeSelect/ModeSelectScene.h"
#include "Title/TitleScene.h"
#include "Result/ResultScene.h"

#include "Pause.h"

#include "Common/SceneManager.h"

class Game
{
	// 変数宣言 ---------------------------------------
private:

	int m_key;
	int m_oldKey;

	// シーン関連
	SceneManager m_sceneManager;

	// プレイ中のステージファイル名
	std::wstring m_stageFileName;

	// プレイ中のモード
	PlayMode m_playMode;

	//　ポーズ
	Pause m_pause;

	// ポーズボタン
	Button m_pauseButton;

	bool m_endFrag;

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

	// ステージファイル
	std::wstring GetStageFileName() const { return m_stageFileName; }
	void SetStageFileName(const std::wstring& fileName) { m_stageFileName = fileName; }

	// プレイモード
	PlayMode GetPlayMode() const { return m_playMode; }
	void SetPlayMode(PlayMode pm) { m_playMode = pm; }

	// 終了関数
	void End();

	bool GetEndFrag() const { return m_endFrag; }
};