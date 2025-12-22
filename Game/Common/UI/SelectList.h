#pragma once
#include "Button.h"

class SelectList
{
	// ----- 変数宣言 ----- //
private:
	// 位置
	Vector2D m_position;

	// 一つの選択肢の大きさ
	Vector2D m_aChouiceSize;

	// 選択肢のリスト
	std::vector<std::wstring> m_choices;

	// 基準のボタン
	Button m_standardButton;

	// 選択肢のボタン
	std::map < std::wstring, std::unique_ptr<Button>> m_choiceButtons;

	// 開いているかどうか
	bool m_isOpen;

	// 選ばれた選択肢
	std::wstring m_choiced;
	int m_choicedIndex;

	// ----- 関数宣言 ----- //
public:
	// コンストラクタ
	SelectList(Vector2D pos, Vector2D size);

	// 初期化
	void Initialize();

	// 更新関数
	void Update();

	// 描画
	void Render();

	// 選択肢の追加
	void AddChoice(std::wstring choice);

	// 選択肢の削除
	void DeleteChoice(std::wstring choice);

	// 選ばれた選択肢を返す関数
	std::wstring GetChoiced();

	// 開いているかを返す関数
	bool GetIsOpen();

	// 位置を返す関数
	const Vector2D& GetPos() const { return m_position; }

	// 位置をセットする関数
	void SetPos(const Vector2D& pos) { m_position = pos; }
};

