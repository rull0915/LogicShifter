#include "LoadCommand.h"

LoadCommand::LoadCommand(StageReceiver& receiver, std::wstring& fileName)
	: UndoEditCommand(receiver)
	, m_fileName{ fileName }
	, m_clearCommand{ receiver }
	, m_setCommands{}
{
}

bool LoadCommand::Execute()
{
	// 盤面のリセット
	m_clearCommand.Execute();

	// ロード
	Load();

	// 全コマンドの実行
	for (auto& command : m_setCommands) command.Execute();

	return true;
}

void LoadCommand::Undo()
{
	// 全コマンドの取り消し
	for (auto& command : m_setCommands) command.Undo();

	// 盤面リセットの取り消し
	m_clearCommand.Undo();
}

void LoadCommand::Redo()
{
	// 盤面リセット
	m_clearCommand.Redo();

	// 全コマンド
	for (auto& command : m_setCommands) command.Redo();
}

void LoadCommand::Load()
{
	// ファイルのロード
	// ファイルから読み込み
	std::ifstream ifs(m_fileName);

	json stage;
	if(ifs.is_open()) ifs >> stage;
	ifs.close();

	PackedCell cell = 0;
	Vector2DInt pos;

	for(auto info : stage["Stage"])
	{
		pos.x = info["PosX"];
		pos.y = info["PosY"];

		CellType type = info["Type"];
		CellType subtype = info["SubType"];

		SetType(cell, type);
		SetSubType(cell, subtype);

		m_setCommands.push_back(SetCommand(m_receiver, pos, cell));
	}
}
