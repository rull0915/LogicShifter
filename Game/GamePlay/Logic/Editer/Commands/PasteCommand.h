#pragma once
#include "UndoEditCommand.h"
#include "SetCommand.h"

class PasteCommand : public UndoEditCommand
{
	// ------ 変数宣言 ------ //
private:

	// 置く位置
	Vector2DInt m_pos;

	// 設置コマンドの配列
	std::vector<SetCommand> m_setCommands;

public:
	PasteCommand(StageReceiver& reciever, Vector2DInt pos);

	bool Execute() override;

	void Undo() override;

	void Redo() override;
};

