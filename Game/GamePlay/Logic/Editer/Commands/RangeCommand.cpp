#include "RangeCommand.h"

RangeCommand::RangeCommand(StageReceiver& reciever, std::pair<Vector2DInt, Vector2DInt> pos)
	: EditCommand(reciever)
	, m_pos{ pos }
{
}

bool RangeCommand::Execute()
{
	Vector2DInt size = { abs(m_pos.first.x - m_pos.second.x), abs(m_pos.first.y - m_pos.second.y) };

	m_receiver.SetCursorSize(size);

	return true;
}
