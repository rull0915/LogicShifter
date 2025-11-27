#include "CommandManager.h"

CommandManager::CommandManager()
	: m_nowCommandNum{ 0 }
	, m_pUndoCommands{}
	, m_pDoCommands{}
{
}

void CommandManager::Initialize()
{
	m_pUndoCommands.clear();
	m_pDoCommands.clear();

	m_nowCommandNum = 0;
}

void CommandManager::AddUndoCommand(std::unique_ptr<UndoEditCommand> pUndoCommand)
{
	// もし実行中が最新じゃなかったら
	if(m_nowCommandNum < static_cast<int>(m_pUndoCommands.size()))
	{
		// 実行中のコマンドより後を削除
		m_pUndoCommands.erase(
			m_pUndoCommands.begin() + (m_nowCommandNum),
			m_pUndoCommands.end()
		);
	}

	// コマンドの追加
	if (pUndoCommand->Execute())
	{
		m_pUndoCommands[m_pUndoCommands.size() - 1].push_back(std::move(pUndoCommand));
	}	
}

void CommandManager::AddDoCommand(std::unique_ptr<EditCommand> pEditCommand)
{
	m_pDoCommands.push_back(std::move(pEditCommand));

	m_pDoCommands[m_pDoCommands.size() - 1]->Execute();
}

void CommandManager::ToNextGroup()
{
	// 追加
	m_pUndoCommands.push_back({});

	m_nowCommandNum++;
}

void CommandManager::UndoCommand()
{
	if(m_nowCommandNum > 0)
	{
		// 戻る
		for(auto& com : m_pUndoCommands[m_nowCommandNum - 1]) com->Undo();

		m_nowCommandNum--;
	}
}

void CommandManager::RedoCommand()
{
	if (m_nowCommandNum < m_pUndoCommands.size())
	{
		// 戻る
		for (auto& com : m_pUndoCommands[m_nowCommandNum]) com->Redo();

		m_nowCommandNum++;
	}
}
