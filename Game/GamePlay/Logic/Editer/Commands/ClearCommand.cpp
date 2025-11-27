#include "ClearCommand.h"

ClearCommand::ClearCommand(StageReceiver& reciever)
	: UndoEditCommand(reciever)
{
}

bool ClearCommand::Execute()
{
	// ステージ全ループ
	for(int i = -OFFSET_Y; i < OFFSET_Y; i++)
	{
		for(int j = -OFFSET_X; j < OFFSET_X; j++)
		{
			// セルを取得
			PackedCell cell = m_receiver.GetCell({ j, i });
			if(cell != 0) 
			{
				// セットコマンド作成
				m_setCommands.push_back(SetCommand(m_receiver, {j, i}, 0));
			}
		}
	}

	for (auto& command : m_setCommands) command.Execute();

	return true;
}

void ClearCommand::Undo()
{
	// 全てを戻す
	for (auto& command : m_setCommands) command.Undo();
}

void ClearCommand::Redo()
{
	for (auto& command : m_setCommands) command.Redo();
}
