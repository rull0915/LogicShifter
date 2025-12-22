#pragma once

#include "../Game/Common/UI/Button.h"
#include "../Common/Scene.h"

#include "../Game/Common/Particles/BaseParticle.h"

class Game;

// モード選択クラス
class ModeSelectScene : public Scene
{
	// --------------- 変数宣言 -------------------- //
private:
	// 親のポインタ
	Game* m_pGame;

	// モードを選ぶボタン
	std::map<PlayMode, std::unique_ptr<Button>> m_buttons;

	// 背景パーティクル
	BaseParticle m_particle;

	// タイトルボタン
	Button m_titleButton;

	// 終了ボタン
	Button m_exitButton;

	// --------------- 関数宣言 --------------------- //
public:

	// コンストラクタ
	ModeSelectScene(Game* pGame);

	// デストラクタ
	~ModeSelectScene() = default;

	// 初期化関数
	void Initialize() override;

	// 更新関数
	void Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// 終了関数
	void Finalize()override;
};

