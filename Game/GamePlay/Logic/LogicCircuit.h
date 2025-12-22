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

	// 選択されたファイル名
	std::wstring m_selectedFileName;

	bool m_toResult;

public:
	LogicCircuit();
	~LogicCircuit();

	void Initialize(PlayMode playMode);

	void Update(float elapsedTime);

	void Render();

	void Finalize();

	// ファイルをセットする関数
	void SetFileName(const std::wstring& fileName) { m_selectedFileName = fileName; }

	bool ToResult() const { return m_toResult; }

private:
	// ブロックの色の保存
	void SaveBlockColors();

	// ブロックの色のロード
	void LoadBlockColors();
};

