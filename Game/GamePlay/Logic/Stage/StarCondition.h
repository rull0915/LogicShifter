#pragma once
#include "../Game/Common/UI/SelectList.h"
#include "TextInputManager.h"

// 3つ星評価の条件設定クラス
class StarCondition
{
	// ----- 定数宣言 ----- //
private:
	const Vector2D SIZE = { Screen::WIDTH * (2.0f / 5), Screen::HEIGHT / 4 };

	// 背景色
	const int BACK_COLOR = 0x767171;
	// 星の色
	const int STAR_COLOR = 0xFFF2CC;

	// セルの文字列
	const std::map<std::wstring, int> CELL_STRINGS =
	{
		{L"Wire", 0b01010000},
		{L"Cross", 0b01100000},
		{L"And", 0b10010000},
		{L"Or", 0b10100000},
		{L"Output", 0b11010000},
		{L"Not", 0b11100000}
	};

	// ----- 変数宣言 ----- //
private:
	// 中心座標
	Vector2D m_pos;

	// 3つ目の条件を決めるリスト
	SelectList m_selectList;

	// 2つ目の条件を受け取るテキストボックス
	TextInputManager m_secondCondition;

	// テキストボックスの変化を受け取る用
	std::wstring m_secondString;
	
	// ----- 関数宣言 ----- //
public:
	StarCondition(Vector2D pos);

	void Initialize();

	void Update();

	void Render();

	void Finalize();

	// 位置を返す関数
	const Vector2D& GetPos() const { return m_pos; }

	// 位置をセットする関数
	void SetPos(const Vector2D& pos) { m_pos = pos; }

	// どれかがアクティブか返す関数
	bool GetIsActive();

	// jsonに保存する関数
	void SaveToJson(json& json);

private:
	// 各要素の位置の更新
	void PosUpdate();

	// 3つ目の条件のどれかがアクティブかどうかを返す関数
	bool GetThirdIsActive();

	// 3つ目の条件の具体的な値を返す関数
	int GetThirdValue();

	// ----- 3つ目の条件別の変数 ----- //

	// 次のセルを不使用
	SelectList m_cd_cell;
	 
	// 指定秒数以内
	TextInputManager m_cd_second;
	std::wstring m_cd_st_second;
	 
	// 指定数以内のセル
	TextInputManager m_cd_count;
	std::wstring m_cd_st_count;

	// 高さ制限
	TextInputManager m_cd_height;
	std::wstring m_cd_st_height;

	// 幅制限
	TextInputManager m_cd_width;
	std::wstring m_cd_st_width;
};

