#pragma once

#include "../EditManager.h"
#include "../StageManager.h"
#include "../FreeManager.h"
#include "../ModeSelect.h"

class LogicCircuit
{
private:

	StageManager m_stageManager;
	FreeManager m_freeManager;
	EditManager m_editManager;

	ModeSelect m_modeSelect;

	PlayMode m_nowPlayMode;

public:
	LogicCircuit();
	~LogicCircuit();

	void Initialize(PlayMode playMode);

	void Update(float elapsedTime);

	void Render();

private:
	// ブロックの色の保存
	void SaveBlockColors();

	// ブロックの色のロード
	void LoadBlockColors();
};

