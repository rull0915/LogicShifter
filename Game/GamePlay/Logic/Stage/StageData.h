#pragma once
#include "../CellInfo.h"

class StageData
{
	// 変数宣言
private:
	// 条件文
	std::wstring m_conditionString;

	// 条件
	std::vector<std::vector<bool>> m_conditions;

	// 入出力数
	int m_inputNum, m_outputNum;

	// 入出力セルの情報
	std::vector<Vector2DInt> m_inputInfo, m_outputInfo;

	// ステージサイズ
	Vector2DInt m_stageSize;

	// ステージ
	std::vector<PackedCell>& m_stage;

	// 関数宣言
public:
	StageData(std::vector<PackedCell>& stage);

	// セーブ
	void Save();

	// ゲッター
	Vector2DInt GetStageSize() const { return m_stageSize; }
	std::wstring GetConditionStr() const { return m_conditionString; }

	// セッター
	void SetConditionStr(std::wstring str) { m_conditionString = str; }
	void SetCondition(int inputNum, int outputNum, bool condition);
	void SetStageSize(Vector2DInt size) { m_stageSize = size; }

	void SetInputNum(int num) { m_inputNum = num; }
	void SetOutputNum(int num) { m_outputNum = num; }

	void SetInputInfo(std::vector<Vector2DInt>& info) { m_inputInfo = info; }
	void SetOutputInfo(std::vector<Vector2DInt>& info) { m_outputInfo = info; }
};

