#include "StageReceiver.h"

StageReceiver::StageReceiver(std::vector<PackedCell>& stage)
	: m_stage{ stage }
	, m_cursorSize{ 1, 1 }
{
}

void StageReceiver::Initialize()
{
	m_cursorSize = { 1, 1 };

	m_copyCells.clear();

	m_cellCounter.clear();

	m_cellsInfo.clear();

	for(auto cell : Cell::ALL_CELL)
	{
		m_cellCounter[cell] = 0;
	}
}

std::vector<PackedCell>& StageReceiver::GetStage()
{
	return m_stage;
}

PackedCell StageReceiver::GetCell(Vector2DInt pos) const
{ 
	if (GetIndex(pos.x, pos.y) >= m_stage.size()) return 0;

	return m_stage[GetIndex(pos.x, pos.y)];
}

void StageReceiver::SetCell(Vector2DInt pos, PackedCell cell)
{
	PackedCell before = GetCell(pos);

	// 置く前のセルのカウンターを減らす
	m_cellCounter[{GetType(before), GetSubType(before)}]--;

	// 置く前のセルの情報を削除
	if(m_stage[GetIndex(pos.x, pos.y)] != 0) DeleteCellInfo({ GetType(before), GetSubType(before) }, pos);

	// セルを置き換え
	m_stage[GetIndex(pos.x, pos.y)] = cell;

	// 置いたセルの情報を追加
	if (std::find(Cell::GET_INFO_TYPES.begin(), Cell::GET_INFO_TYPES.end(), std::make_pair(GetType(cell), GetSubType(cell))) != Cell::GET_INFO_TYPES.end()) m_cellsInfo[{GetType(cell), GetSubType(cell)}].push_back({ pos });

	// 置いたセルのカウンターを増やす
	m_cellCounter[{GetType(cell), GetSubType(cell)}]++;
}

std::unordered_map<Vector2DInt, PackedCell>& StageReceiver::GetCopyCells()
{
	return m_copyCells;
}

void StageReceiver::SetCopyCells(std::unordered_map<Vector2DInt, PackedCell>& copyCells)
{
	m_copyCells = copyCells;
}

void StageReceiver::CopyInverse(bool isHorizontal)
{
	auto save = m_copyCells;

	m_copyCells.clear();

	int maxX = 0, maxY = 0;

	for (auto cell : save)
	{
		if (maxX < cell.first.x) maxX = cell.first.x;
		if (maxY < cell.first.y) maxY = cell.first.y;
	}

	for (auto cell : save)
	{
		Vector2DInt pos;
		if (isHorizontal)
		{
			pos = { maxX - cell.first.x, cell.first.y };
		}
		else
		{
			pos = { cell.first.x, maxY - cell.first.y };
		}
		m_copyCells[pos] = cell.second;
	}
}

bool StageReceiver::DeleteCellInfo(CellTypes types, Vector2DInt pos)
{
	for (int i = 0; i < m_cellsInfo[types].size(); i++) 
	{
		if(m_cellsInfo[types][i] == pos) 
		{
			m_cellsInfo[types].erase(m_cellsInfo[types].begin() + i);

			return true;
		}
	}

	return false;
}
