#pragma once
#include "../Game/GamePlay/Logic/CellInfo.h"

// 条件チェック抽象クラス
class BaseChecker
{
	// ----- 変数宣言 ----- //
protected:
	// 値
	int m_value;

	// 固定ブロックの座標の参照

	// ----- 関数宣言 ----- //
public:
	// コンストラクタ
	BaseChecker(int value) : m_value{ value } {};

	virtual ~BaseChecker() = default;

	// 判定関数
	virtual bool IsSatisfied() = 0;
};

