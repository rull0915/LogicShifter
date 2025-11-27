#pragma once
#include "UndoEditCommand.h"
#include "SetCommand.h"
#include "ClearCommand.h"

class LoadCommand : public UndoEditCommand
{
	// ----- 変数宣言 ----- //
private:
	// ファイル名
	std::wstring m_fileName;

	// セットコマンド群
	std::vector<SetCommand> m_setCommands;

	// クリアコマンド
	ClearCommand m_clearCommand;

	// ----- 関数宣言 ----- //
public:
	LoadCommand(StageReceiver& receiver, std::wstring& fileName);

	bool Execute() override;

	void Undo() override;

	void Redo() override;

private:
	void Load();
};

