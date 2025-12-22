#pragma once
#include "BaseChecker.h"

// 条件: 指定セルを使用しない
class TimeChecker : public BaseChecker
{
	// ----- 変数宣言 ----- //
private:
	// クリアタイム
	float m_clearTime;

	// ----- 関数宣言 ----- //
public:
	TimeChecker(int value, float clearTime);

	bool IsSatisfied() override;
};