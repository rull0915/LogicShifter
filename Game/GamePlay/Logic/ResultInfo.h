#pragma once
#include "Condition.h"

// 3つ目の星の条件群
static const std::vector<std::wstring> THIRD_CONDITIONS =
{
	L"次のセルを不使用",
	L"指定秒数以内",
	L"指定数以内のセル",
	L"指定の高さに収める",
	L"指定の幅に収める"
};

// リザルト情報構造体
// シングルトン
class ResultInfo
{
private:
	// ステージ名
	std::wstring m_stageName;

	// クリア条件
	std::vector<Condition> m_conditions;

	// 各条件を満たしたか
	bool m_isSatisfied[3];

	// 第二条件の値
	int m_secondConditionValue;

	// 第三条件の条件
	std::wstring m_thirdCondition;

	// 第三条件の値
	int m_thirdConditionValue;

	// ----- 関数宣言 ----- //
private:
	ResultInfo()
		: m_stageName{}
		, m_isSatisfied{ false, false, false }
		, m_secondConditionValue{ -1 }
		, m_thirdCondition{}
		, m_thirdConditionValue{ -1 }
	{
	};
	
	~ResultInfo() = default;

public:
	static ResultInfo& GetInstance()
	{
		static ResultInfo instance;

		return instance;
	}

	// ----- ゲッター ----- //
	
	// ステージ名
	std::wstring GetStageName() const { return m_stageName; }

	// クリア条件
	std::vector<Condition> GetConditions() const { return m_conditions; }

	// 各条件を満たしたか
	bool GetIsSatisfied(int index) const { return m_isSatisfied[index]; };

	// 第二条件の値
	int GetSecondConditionValue() const { return m_secondConditionValue; };

	// 第三条件の条件
	std::wstring GetThirdCondition() const { return m_thirdCondition; };

	// 第三条件の値
	int GetThirdConditionValue() const { return m_thirdConditionValue; };

	// ----- セッター ----- //

	// ステージ名
	void SetStageName(std::wstring name) { m_stageName = name; }

	// クリア条件
	void SetConditions(std::vector<Condition> cond) { m_conditions = cond; }

	// 各条件を満たしたか
	void SetIsSatisfied(int index, bool is) { m_isSatisfied[index] = is; };

	// 第二条件の値
	void SetSecondConditionValue(int val) { m_secondConditionValue = val; };

	// 第三条件の条件
	void SetThirdCondition(std::wstring name) { m_thirdCondition = name; };

	// 第三条件の値
	void SetThirdConditionValue(int val) { m_thirdConditionValue = val; };
};