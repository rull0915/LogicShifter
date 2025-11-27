#pragma once
#include "ModeManager.h"

#include "Logic/Editer/CircuitEditer.h"
#include "Logic/ClearChecker.h"
#include "Logic/Condition.h"

// ステージモードのマネージャークラス
class StageManager : public ModeManager
{
	// 変数宣言
private:

	// --------- 条件関連 --------- //

	// 入出力セルの位置
	Conditions m_conditions;

	// 条件文
	std::wstring m_conditionString;

	// -------- ステージ関連 -------- //

	// 固定ブロックの位置
	std::unordered_set<Vector2DInt> m_fixedPos;

	// エディタ
	CircuitEditer m_circuitEditer;

	// クリア判定クラス
	ClearChecker m_clearChecker;

	// -------- その他 ---------- //

	// クリアチェックに移行するボタン
	Button m_clearCheckButton;

	// クリアフラグ(テスト用)
	bool m_clearFrag;

public:
	StageManager();

	void Initialize() override;

	void Update(float elapsedTime) override;

	void Render() override;

	void Load(std::wstring fileName);
};
