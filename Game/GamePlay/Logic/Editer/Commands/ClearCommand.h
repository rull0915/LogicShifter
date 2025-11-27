#pragma once
#include "UndoEditCommand.h"
#include "SetCommand.h"

class ClearCommand : public UndoEditCommand
{
	// ------ •Ï”éŒ¾ ------ //
private:

	// ’u‚­ˆÊ’u
	std::vector<SetCommand> m_setCommands;

public:
	ClearCommand(StageReceiver& reciever);

	bool Execute() override;

	void Undo() override;

	void Redo() override;
};

