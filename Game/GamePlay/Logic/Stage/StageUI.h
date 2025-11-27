#pragma once
#include "../UI/Button.h"
#include "TextInputManager.h"
#include "Switch.h"
#include "StageData.h"

class Setting;

class StageUI
{
	// 状態の列挙型
	enum class State
	{
		Opening,
		Closing,
		Hide,
		Exist,
	};

	// ----- 定数宣言 ----- //

public:

	// ボタンのサイズ
	static constexpr Vector2D BUTTON_SIZE = { 16, 32 };

	// ----- 変数宣言 ----- //

private:
	// 条件文入力ボックス
	TextInputManager m_textInputManager;

	// ステージサイズ入力ボックス
	TextInputManager m_widthInput, m_heightInput; 

	// 条件文
	std::wstring m_conditionString, m_widthStr, m_heightStr;
	
	// 開閉ボタン
	Button m_button;

	// 今の状態
	State m_nowState;

	// 位置
	Vector2D m_position;

	// イージング用変数
	float m_easingX;

	// 設定
	std::vector<std::unique_ptr<Setting>> m_settings;

	// スクロールの高さ
	float m_scrollHeight;

	// 入出力の数
	int m_inputNum, m_outputNum;

	// データの参照
	StageData& m_stageData;

	// ----- 関数宣言 ----- //
public:
	StageUI(StageData& stageData);

	void Initialize();

	void Update(float);

	void Render();

	void SetInputNum(int num) { m_inputNum = num; }
	void SetOutputNum(int num) { m_outputNum = num; }

	bool PointIsOnMe(Vector2D point);
private:

	void StateUpdate(float);
};

class Setting
{
public:
	static constexpr Vector2D BOX_SIZE = { Screen::WIDTH * (2.0f / 5) * (4.0f / 5), Screen::HEIGHT / 8 };

private:
	// 位置
	Vector2D m_position;

	// 入出力の数
	int m_inputNum;
	int m_outputNum;

	// 状況
	bool* m_inputs;
	bool* m_outputs;

	// スイッチ
	std::vector<std::unique_ptr<Switch>> m_switches;

	// ----- 関数宣言 ----- //

public:
	// コンストラクタ
	Setting(int num);

	void Initialize();

	// 描画
	void Render();

	// 更新
	void Update(float);

	// 数の変更
	void ChangeInputNum(int num) {
		if (num > Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_INPUT}]) return;
		m_inputNum = num;
	}
	void ChangeOutputNum(int num) {
		if (num > Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_OUTPUT}]) return;
		m_outputNum = num; 
	}

	void SetPos(Vector2D pos) { m_position = pos; }

	bool GetCondition(int outputNum)
	{
		if (outputNum >= Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_OUTPUT}]) return false;

		return m_outputs[outputNum];
	}
};
