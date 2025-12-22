#pragma once
#include "ModeManager.h"

#include "Logic/Editer/CircuitEditer.h"
#include "Logic/ClearChecker.h"
#include "Logic/Condition.h"

#include "Logic/ConditionChecker/Checkers.h"
#include "Logic/ResultInfo.h"

#include "Logic/Tutorial/BaseTutorial.h"

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

	// クリアフラグ
	bool m_clearFrag;

	// 条件判定ポインタ
	std::unique_ptr<BaseChecker> m_conditionChecker;

	// 条件のID
	int m_conditionID;

	// 経過時間
	float m_sumElapsedTime;

	// 実行回数
	int m_executeNum;

	// リザルトへ移行するかどうか
	bool m_toResult;

	std::unique_ptr<Tutorial> m_pTutorial;

public:
	StageManager();

	void Initialize() override;

	void Update(float elapsedTime) override;

	void Render() override;

	void Finalize() override;

	void Load(std::wstring fileName);

	bool ToResult() const { return m_toResult; }

private:

	// 条件判定関数
	void CheckConditions();
};
