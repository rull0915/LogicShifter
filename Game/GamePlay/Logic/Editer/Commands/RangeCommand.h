#pragma once
#include "EditCommand.h"

class RangeCommand : public EditCommand
{
	// ----- •Ï”éŒ¾ ----- //
private:
	// ƒRƒs[”ÍˆÍ
	std::pair<Vector2DInt, Vector2DInt> m_pos;

public:
	RangeCommand(StageReceiver& reciever, std::pair<Vector2DInt, Vector2DInt> pos);

	bool Execute() override;
};

