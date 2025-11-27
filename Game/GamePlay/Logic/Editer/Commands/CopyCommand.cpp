#include "CopyCommand.h"

CopyCommand::CopyCommand(StageReceiver& reciever, std::pair<Vector2DInt, Vector2DInt> pos)
	: EditCommand(reciever)
	, m_pos{ pos }
{
}

bool CopyCommand::Execute()
{
	// コピー用
	std::unordered_map<Vector2DInt, PackedCell> copy;

	// 範囲内をループ
	for(int i = m_pos.first.y; i < m_pos.second.y; i++)
	{
		for(int j = m_pos.first.x; j < m_pos.second.x; j++)
		{
			// セルが存在していたら
			PackedCell cell = m_receiver.GetCell(Vector2DInt{ j, i });

			if (cell != 0)
			{
				copy[{j - m_pos.first.x, i - m_pos.first.y}] = cell;
			}
		}
	}

	// 代入
	m_receiver.SetCopyCells(copy);

	return true;
}
