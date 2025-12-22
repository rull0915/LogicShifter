#pragma once

#include "../Game/Common/UI/Button.h"
#include "../CellInfo.h"
#include "../Game/Common/UI/ColorPallet.h"
#include "../Game/Common/UI/TextBox.h"

class CircuitEditer;

// 状態の列挙型
enum class State
{
	Opening,
	Closing,
	Hide,
	Exist,
};

// 機能の列挙型
enum class Function
{
	Save = 0,
	Load,
	Reset,
	Copy,
	Paste,
	Range,
	Vertical,
	Horizontal,
	Clear,
	Undo,
	Redo,

	// 機能数
	FunctionNum,
};

class SelectUI
{
	// ボタンのサイズ
	static constexpr Vector2D BUTTON_SIZE = { 16, 32 };

	// 存在するボタンの種類
	std::unordered_map<PlayMode, std::vector<Function>> BUTTON_NAMES = 
	{ 
		{
			PlayMode::Edit,
			{Function::Save, Function::Load, Function::Reset, Function::Copy, Function::Paste, Function::Range, Function::Vertical, Function::Horizontal, Function::Clear, Function::Undo}
		},
		{
			PlayMode::Free,
			{Function::Reset, Function::Copy, Function::Paste, Function::Range, Function::Vertical, Function::Horizontal, Function::Clear, Function::Undo, Function::Redo, Function::Save, Function::Load}
		},
		{
			PlayMode::Stage,
			{ Function::Undo, Function::Redo }
		},
	};

	std::unordered_map<Function, std::pair<std::string, std::wstring>> buttonExplains =
	{
		{Function::Save,		{ "Save"		, L"Save: 現在作成中のステージを保存します"}},
		{Function::Load,		{ "Load"		, L"Load: ステージ情報を読み込みます"}},
		{Function::Reset,		{ "Reset"		, L"Reset: 設置モードをリセットします"}},
		{Function::Copy,		{ "Copy"		, L"Copy: 範囲を選択し、コピーします"}},
		{Function::Paste,		{ "Paste"		, L"Paste: コピーしたものを貼り付けます"}},
		{Function::Range,		{ "Range"		, L"Range: 選択範囲を決めます"}},
		{Function::Horizontal,	{ "Horizontal"	, L"Horizontal: コピーしたものを左右反転します"}},
		{Function::Vertical,	{ "Vertical"	, L"Vertical: コピーしたものを上下反転します"}},
		{Function::Clear,		{ "Clear"		, L"Clear: ステージをリセットします"}},
		{Function::Undo,		{ "Undo"		, L"Undo: 一手戻ります"}},
		{Function::Redo,		{ "Redo"		, L"Undo: 一手進めます"}},
	};

	std::wstring blockExplain = L"Block: 左クリック 設置するブロックの変更 右クリック 色の変更";

	std::map < std::pair < CellType, CellSubType > , std::wstring > blockButtonExplains =
	{
		{{TYPE_WIRE, SUBTYPE_NORMAL},	L"Wire: 信号を伝える導線"},
		{{TYPE_WIRE, SUBTYPE_CROSS},	L"Cross: 交差可能な導線"},
		{{TYPE_WIRE, SUBTYPE_LIGHT},	L"Light: 明るい導線"},
		{{TYPE_OTHERS, SUBTYPE_WALL},	L"Wall: 信号を遮断する壁"},
		{{TYPE_INPUT, SUBTYPE_AND},		L"And: 隣接ワイヤ全てが信号を持っている時のみ信号を発する"},
		{{TYPE_INPUT, SUBTYPE_OR},		L"Or: 隣接ワイヤのどれかが信号を持っている時信号を発する"},
		{{TYPE_INPUT, SUBTYPE_BUTTON},	L"Button: ON/OFF切り替え可能なボタン"},
		{{TYPE_OUTPUT, SUBTYPE_NORMAL},	L"Output: And, Or, Xor等入力セルの信号を受け取れる"},
		{{TYPE_OUTPUT, SUBTYPE_NOT},	L"Not: 信号がONの時OFF, OFFの時ONになる"},
		{{TYPE_OTHERS, SUBTYPE_INPUT},	L"Input: 入力されるセル"},
		{{TYPE_OTHERS, SUBTYPE_OUTPUT},	L"Output: 出力セル"}
	};

private:
	// 今の状態
	State m_nowState;

	// 位置(左上)
	Vector2D m_position;

	// イージング用変数
	float m_easingX;

	// スライドボタン
	Button m_slideButton;

	// ボタン
	std::unordered_map<Function, std::unique_ptr<Button>> m_buttons;
	std::unique_ptr<Button> m_blockExButton;

	// ブロック選択ボタン
	std::map<std::pair<CellType, CellSubType>, std::pair<std::unique_ptr<Button>, std::unique_ptr<Button>>> m_blockButtons;

	// このUIの親のポインタ
	CircuitEditer* m_pParent;

	// テキストボックス
	TextBox m_textBox;

	// テスト用
	ColorPallet m_colorPallet;

public:
	SelectUI(CircuitEditer* pParent);

	void Initialize(PlayMode playMode);

	void Update(float elapsedTime);

	void Render();

	void Finalize();

	// 指定したスクリーン座標がUI内にあるかどうか
	bool GetInSelectUI(Vector2DInt screenPos);

	void SetState(State state);

private:
	// ステートの更新
	void StateUpdate(float elapsedTime);
};

// 色変更時のボタン
class ColorButtons
{
private:
	// 位置
	Vector2D m_position;

	Button m_colorButton;
	Button m_signalColorButton;

	// ボタン説明テキスト
	TextBox m_textBox;

public:
};
