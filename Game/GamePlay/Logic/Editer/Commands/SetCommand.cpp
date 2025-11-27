#include "SetCommand.h"

SetCommand::SetCommand(StageReceiver& reciever, Vector2DInt pos, PackedCell cell)
	: UndoEditCommand(reciever)
	, m_pos{ pos }
	, m_after{ cell }
	, m_before{ m_receiver.GetCell(pos) }
{
}

bool SetCommand::Execute()
{
	if ((m_pos.x < -OFFSET_X || m_pos.x >= STAGE_WIDTH - OFFSET_X) || (m_pos.y < -OFFSET_Y || m_pos.y >= STAGE_HEIGHT - OFFSET_Y)) return false;

	if (GetType(m_before) == GetType(m_after) 
		&& GetSubType(m_before) == GetSubType(m_after) ) return false;

	if (m_receiver.GetCellCount({ GetType(m_after), GetSubType(m_after) }) >= Cell::CELL_MAX_COUNT[{GetType(m_after), GetSubType(m_after)}]) return false;

	// ê›íu
	m_receiver.SetCell(m_pos, m_after);

	return true;
}

void SetCommand::Undo()
{
	// å≥Ç…ñﬂÇ∑
	m_receiver.SetCell(m_pos, m_before);
}

void SetCommand::Redo()
{
	// å≥Ç…ñﬂÇ∑
	m_receiver.SetCell(m_pos, m_after);
}
