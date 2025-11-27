#pragma once

#include "EditCommand.h"

class UndoEditCommand : public EditCommand
{
public:
	UndoEditCommand(StageReceiver& reciever)
		: EditCommand(reciever)
	{
	};
	~UndoEditCommand() = default;

	virtual void Undo() = 0;

	virtual void Redo() = 0;
};
