#pragma once
#include "../Game/Common/UI/SlideBar.h"
#include "../Game/Common/UI/Button.h"
#include "GamePlay/Logic/Stage/Switch.h"

// ゲームの設定クラス
class GameSetting
{
	// ----- 変数宣言 ----- //
private:
	// BGM設定バー
	SlideBar m_bgmBar;

	// SE設定バー
	SlideBar m_seBar;

	// アクティブフラグ
	bool m_isActive;

	// 終了ボタン
	Button m_finishButton;

	// ----- 関数宣言 ----- //
public:
	GameSetting();

	void Initialize();

	void Update();

	void Render();

	bool GetIsActive() const { return m_isActive; }
	void SetIsActive(bool a) { m_isActive = a; }
};

