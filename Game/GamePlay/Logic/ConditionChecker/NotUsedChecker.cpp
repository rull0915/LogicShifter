#include "NotUsedChecker.h"

NotUsedChecker::NotUsedChecker(int value, std::vector<PackedCell>& cells, std::unordered_set<Vector2DInt>& fixedPos)
	: BaseChecker(value)
	, m_cells{ cells }
	, m_fixedPos{ fixedPos }
{
}

bool NotUsedChecker::IsSatisfied()
{
	// 目標のセル
	int targetType = GetType(m_value);
	int targetSubType = GetSubType(m_value);

	// 全セル捜査
	for(int i = -OFFSET_Y; i < OFFSET_Y; i++)
	{
		for (int j = -OFFSET_X; j < OFFSET_X; j++) 
		{
			PackedCell cell = m_cells[GetIndex(j, i)];

			int type = GetType(cell);
			int sType = GetSubType(cell);

			// 目標のセルがあれば
			if (type == targetType && sType == targetSubType)
			{
				bool isFixed = false;

				// 固定セルに含まれているかチェック
				for (auto& pos : m_fixedPos)
				{
					if (pos == Vector2DInt{j, i})
					{
						isFixed = true;
						break;
					}
				}

				if (!isFixed) return false;
			}
		}
	}

	return true;
}
