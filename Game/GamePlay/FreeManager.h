#pragma once

#include "ModeManager.h"

#include "Logic/CircuitSimulator.h"
#include "Logic/Editer/CircuitEditer.h"

class FreeManager : public ModeManager
{
	// 自動再生時の更新間隔
	static constexpr float UPDATE_DISTANCE = 1.0f / 10;
	static constexpr float UPDATE_DISTANCE_FAST = 1.0f / 30;
	static constexpr float UPDATE_DISTANCE_FASTTEST = 1.0f / 1000;

	static constexpr Vector2D BUTTON_SIZE = { 50, 50 };

	std::unordered_map<std::string, std::pair<Vector2D, std::wstring>> buttonInfos =
	{
		{ "Stop"		, {{ 70 , 70},		L"停止"}},
		{ "PlayOnce"	, {{ 130, 70},		L"1回実行"}},
		{ "Play"		, {{ 190, 70},		L"再生"}},
		{ "PlayFast"	, {{ 250, 70},		L"早送り"}},
	};

private:

	CircuitEditer m_circuitEditer;
	CircuitSimulator m_circuitSimulator;

	// 実行ボタン
	std::map<std::string, std::unique_ptr<Button>> m_playButtons;
	TextBox m_textBox;

	// スピード
	float m_nowElapsedTime;
	float m_playSpeed;

public:
	FreeManager();
	~FreeManager();

	void Initialize() override;

	void Update(float elapsedTime) override;

	void Render() override;

	void Finalize() override;
};

