#pragma once
#include "BaseChecker.h"

// 条件: 指定セルを使用しない
class HeightChecker : public BaseChecker
{
	// ----- 変数宣言 ----- //
private:
	// ステージの参照
	std::vector<PackedCell>& m_cells;

	// 固定ブロックの位置の参照
	std::unordered_set<Vector2DInt>& m_fixedPos;

	// ----- 関数宣言 ----- //
public:
	HeightChecker(int value, std::vector<PackedCell>& cells, std::unordered_set<Vector2DInt>& fixedPos);

	bool IsSatisfied() override;
};