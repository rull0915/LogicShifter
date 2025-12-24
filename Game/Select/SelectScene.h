#pragma once

#include "../Game/Common/Scene.h"
#include "../Game/Common/UI/Button.h"
#include "../Game/Common/Particles/BaseParticle.h"

// クラスの前方宣言
class Game;

class SelectScene : public Scene
{
	// 定数宣言
public:

	// 変数宣言
private:
	// このシーンを含むゲームオブジェクトへのポインタ
	Game* m_pGame;

	// ステージ情報
	std::vector<std::wstring> m_stageFileName;

	// お題
	std::vector<std::wstring> m_stageNames;

	// ステージのスクリーン
	std::vector<int> m_ghScreens;

	// 選択中のステージ番号
	int m_selectedNum;

	// 移動ボタン
	std::pair<Button, Button> m_moveButton;

	// スタートボタン
	Button m_startButton;

	// 背景パーティクル
	BaseParticle m_particle;

	// 関数宣言 -------------------------------
public:

	// コンストラクタ
	SelectScene(Game* pGame);

	// デストラクタ
	~SelectScene();

	// 初期化関数
	void Initialize() override;

	// 更新関数
	void Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// 終了関数
	void Finalize()override;
};