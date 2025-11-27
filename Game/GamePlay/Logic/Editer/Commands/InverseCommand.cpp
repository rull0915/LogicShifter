#include "InverseCommand.h"

InverseCommand::InverseCommand(StageReceiver& reciever, bool isHorizontal)
	: EditCommand(reciever)
	, m_isHorizontal{ isHorizontal }
{
}

bool InverseCommand::Execute()
{
	m_receiver.CopyInverse(m_isHorizontal);

	return true;
}
