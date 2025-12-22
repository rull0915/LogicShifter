#include "HeightChecker.h"

HeightChecker::HeightChecker(int value, std::vector<PackedCell>& cells, std::unordered_set<Vector2DInt>& fixedPos)
	: BaseChecker(value)
	, m_cells{ cells }
	, m_fixedPos{ fixedPos }
{
}

bool HeightChecker::IsSatisfied()
{
	// y座標最小最大
	int minY = INT_MAX, maxY = INT_MIN;

	// 全セル捜査
	for (int i = -OFFSET_Y; i < OFFSET_Y; i++)
	{
		for (int j = -OFFSET_X; j < OFFSET_X; j++)
		{
			PackedCell cell = m_cells[GetIndex(j, i)];

			// 目標のセルがあれば
			if (cell != 0)
			{
				bool isFixed = false;

				// 固定セルに含まれているかチェック
				for (auto& pos : m_fixedPos)
				{
					if (pos == Vector2DInt{ j, i })
					{
						isFixed = true;
						break;
					}
				}

				if (!isFixed)
				{
					if (i > maxY) maxY = i;
					if (i < minY) minY = i;
				}
			}
		}
	}

	return (maxY - minY + 1 <= m_value);
}
