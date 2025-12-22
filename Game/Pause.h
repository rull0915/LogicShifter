#pragma once
#include "Common/UI/Button.h"
#include "../Game/Common/Scene.h"

class Game;

// シングルトンのポーズクラス
class Pause : public Scene
{
public:
	// 状態列挙型
	enum class State
	{
		None,
		StageMode,
		OtherMode,
		StageSelect,
	};

	// ----- 変数宣言 ----- //
private:
	State m_nowState;

	// アクティブフラグ
	bool m_isActive;

	// --- ボタン --- //
	Button m_resume;

	Button m_retry;

	Button m_stageSelect;

	Button m_modeSelect;

	// --- 無効ボタン --- //
	Button m_invalidResume;

	Button m_invalidRetry;

	Button m_invalidStageSelect;

	Button m_invalidModeSelect;

	// カーソル位置
	float m_cursorPos;

	// ----- 関数宣言 ----- //
public:
	Pause(Game* pGame);

	void Initialize(State state);
	void Initialize() override {};

	void Update(float elapsedTime) override;

	void Render() override;

	void Finalize() override;

	// アクティブフラグを返す関数
	bool GetIsActive() const { return m_isActive; }

private:
	void DrawStageInfo();

	void CursorUpdate();
};

