#pragma once
#include "../Game/Common/Scene.h"
#include "../Game/Common/UI/SelectList.h"
#include "../Game/GamePlay/Logic/Stage/StarCondition.h"

class Game;

class TitleScene : public Scene
{
	// 定数宣言
	const wchar_t* TITLE = L"CircuitMaker";

	// 変数宣言
private:
	// このシーンを含むゲームオブジェクトへのポインタ
	Game* m_pGame;

	// 背景のフィールド
	int m_backGround[36][64];

	int m_backScreen;

	// スタートボタン
	Button m_startButton;

	// 関数宣言 -------------------------------
public:

	// コンストラクタ
	TitleScene(Game* pGame);

	// デストラクタ
	~TitleScene();

	// 初期化関数
	void Initialize() override;

	// 更新関数
	void Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// 終了関数
	void Finalize()override;

private:

	// スクリーン座標からグリッド描画を返す関数
	Vector2DInt ToGrid(Vector2D pos);

	// ランダムな色を返す関数
	int GetRandColor();

	void LoadTitleMap();
};

