#pragma once
#include "BaseChecker.h"

// 条件: 指定セルを使用しない
class NotUsedChecker : public BaseChecker
{
	// ----- 変数宣言 ----- //
private:

	// ----- 関数宣言 ----- //
	bool IsSatisfied() override;
};