#pragma once

#include "ModeManager.h"

#include "Logic/Stage/StageUI.h"
#include "Logic/Editer/CircuitEditer.h"

#include "Logic/Stage/StageData.h"

class EditManager : public ModeManager
{
private:

	// エディタ
	CircuitEditer m_circuitEditer;

	// データ
	StageData m_stageData;

	// ステージ設定UI
	StageUI m_stageUi;

	// セーブボタン
	Button m_saveButton;

	bool m_canUpdate;

public:
	EditManager();
	~EditManager();

	void Initialize() override;

	void Update(float elapsedTime) override;

	void Render() override;

	void Finalize() override;
};

