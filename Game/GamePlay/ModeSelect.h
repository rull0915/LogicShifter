#pragma once

#include "Logic/UI/Button.h"

// 親クラスの前方宣言
class LogicCircuit;

// モード選択クラス
class ModeSelect
{
	// --------------- 変数宣言 -------------------- //
private:
	// 親のポインタ
	LogicCircuit* m_pParent;

	// モードを選ぶボタン
	std::map<PlayMode, std::unique_ptr<Button>> m_buttons;

	// --------------- 関数宣言 --------------------- //
public:
	ModeSelect(LogicCircuit* parent);

	void Initialize();

	void Update(float elapsedTime);

	void Render();
};

