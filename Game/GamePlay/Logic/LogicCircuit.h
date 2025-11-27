#pragma once

#include "../EditManager.h"
#include "../StageManager.h"
#include "../FreeManager.h"

class LogicCircuit
{
private:

	StageManager m_stageManager;
	FreeManager m_freeManager;
	EditManager m_editManager;

	PlayMode m_nowPlayMode;

public:
	LogicCircuit();
	~LogicCircuit();

	void Initialize(PlayMode playMode);

	void Update(float elapsedTime);

	void Render();

	bool IsReset()
	{
		return  m_stageManager.IsReset() || m_freeManager.IsReset() || m_editManager.IsReset();
	}

private:
	// ブロックの色の保存
	void SaveBlockColors();

	// ブロックの色のロード
	void LoadBlockColors();
};

