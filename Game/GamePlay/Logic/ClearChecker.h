#pragma once
#include "CircuitSimulator.h"

#include "CellInfo.h"

#include "Condition.h"

#include "../Game/Common/UI/Gauge.h"

class ClearChecker
{
	static constexpr int MAX_GENERATION = 100;

private:

	// ステージ参照
	std::vector<PackedCell>& m_stage, m_nextStage;

	// 実行前のステージ
	std::vector<PackedCell> m_beforeStage;

	// 実行用
	CircuitSimulator m_circuitSimulator;

	// 条件
	Conditions& m_conditions;

	// 現在チェック中の条件番号
	int m_nowCheckingNum;

	// 現在の実行速度
	float m_nowPlaySpeed;

	// 経過時間
	float m_nowElapsedTime;

	// クリアチェック中かどうか
	bool m_isActive;

	// ゲージ
	Gauge m_gauge;

public:
	ClearChecker(std::vector<PackedCell>& m_stage, std::vector<PackedCell>& m_nextStage, Conditions& con);

	void Initialize(std::vector<PackedCell>& stage);

	bool Update(float elapsedTime);

	void Render();

	// クリア判定中かどうかを返す関数
	bool GetIsActive() const { return m_isActive; }

private:
	// 次の条件へ移行する関数
	void ToNextCondition();

	// 条件の判定をする関数
	bool CheckCondition();
};
