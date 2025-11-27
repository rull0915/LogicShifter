#pragma once
#include "Commands/UndoEditCommand.h"

// command管理クラス
class CommandManager
{
	// ----- 変数宣言 ----- //
private:
	// Undo可能commandの配列
	std::vector<std::vector<std::unique_ptr<UndoEditCommand>>> m_pUndoCommands;

	// Undo不可commandの配列
	std::vector<std::unique_ptr<EditCommand>> m_pDoCommands;

	// 現在実行中のコマンド
	int m_nowCommandNum;

	// ----- 関数宣言 ----- //
public:
	CommandManager();

	void Initialize();

	void AddUndoCommand(std::unique_ptr<UndoEditCommand> pUndoCommand);
	void AddDoCommand(std::unique_ptr<EditCommand> pUndoCommands);

	void ToNextGroup();

	void UndoCommand();
	void RedoCommand();
};

