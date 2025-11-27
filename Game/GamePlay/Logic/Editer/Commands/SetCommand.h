#pragma once
#include "UndoEditCommand.h"

class SetCommand : public UndoEditCommand
{
	// ------ 変数宣言 ------ //
private:
	// 置く前後のセル
	PackedCell m_before;
	PackedCell m_after;

	// 置く位置
	Vector2DInt m_pos;

public:
	SetCommand(StageReceiver& reciever, Vector2DInt pos, PackedCell cell);

	bool Execute() override;

	void Undo() override;

	void Redo() override;
};

