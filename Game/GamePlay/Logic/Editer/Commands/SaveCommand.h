#pragma once
#include "EditCommand.h"
class SaveCommand : public EditCommand
{
	// ----- •Ï”éŒ¾ ----- //
private:
	// ƒtƒ@ƒCƒ‹–¼
	std::wstring m_fileName;

public:
	SaveCommand(StageReceiver& reciever, std::wstring fileName);

	bool Execute() override;
};
