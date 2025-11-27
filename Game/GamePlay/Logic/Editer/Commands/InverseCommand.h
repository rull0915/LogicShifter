#pragma once
#include "EditCommand.h"

class InverseCommand : public EditCommand
{
	// ----- •Ï”éŒ¾ ----- //
private:
	// ¶‰E‚©ã‰º‚©
	bool m_isHorizontal;

public:
	InverseCommand(StageReceiver& reciever, bool isHorizontal);

	bool Execute() override;
};
