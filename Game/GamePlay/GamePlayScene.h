#pragma once

#include "DxLib.h"
#include "../Common/Scene.h"

#include "Logic/LogicCircuit.h"

#include "../Camera.h"

#include "../Game/Common/UI/Gauge.h"

// クラスの前方宣言
class Game;

class GamePlayScene : public Scene
{
	// 定数宣言
public:

	// 変数宣言
private:
	// このシーンを含むゲームオブジェクトへのポインタ
	Game* m_pGame;

	LogicCircuit m_logic;

	// 関数宣言 -------------------------------
public:

	// コンストラクタ
	GamePlayScene(Game* pGame);

	// デストラクタ
	~GamePlayScene();

	// 初期化関数
	void Initialize() override;

	// 更新関数
	void Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// 終了関数
	void Finalize()override;

private:
	// スケール変化
	void ChangeScale(float newScale);
};