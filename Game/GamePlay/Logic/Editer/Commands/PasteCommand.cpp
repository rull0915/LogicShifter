#include "PasteCommand.h"

PasteCommand::PasteCommand(StageReceiver& reciever, Vector2DInt pos)
	: UndoEditCommand(reciever)
	, m_pos{ pos }
	, m_setCommands{}
{
}

bool PasteCommand::Execute()
{
	// コピーセル分ループ
	for(auto& copy : m_receiver.GetCopyCells())
	{
		m_setCommands.push_back(SetCommand(m_receiver, m_pos + copy.first, copy.second));
	}

	// コマンドを実行
	for (auto& command : m_setCommands) command.Execute();

	return true;
}

void PasteCommand::Undo()
{
	// 元に戻す
	for (auto command : m_setCommands) command.Undo();
}

void PasteCommand::Redo()
{
	// 元に戻す
	for (auto command : m_setCommands) command.Redo();
}
