#pragma once
#include "../CellInfo.h"

// Receiverクラス
// 処理を実際に実行する
class StageReceiver
{
	// ------ 変数宣言 ------ //
private:
	// ステージ
	std::vector<PackedCell>& m_stage;

	// コピーしたセル
	std::unordered_map<Vector2DInt, PackedCell> m_copyCells;

	// カーソルの大きさ
	Vector2DInt m_cursorSize;

	// 各セルの数
	std::map < CellTypes, int > m_cellCounter;

	// 各セルの情報
	std::map<CellTypes, std::vector<Vector2DInt>> m_cellsInfo;

	// ------ 関数宣言 ------ //
public:
	StageReceiver(std::vector<PackedCell>& stage);

	// 初期化処理
	void Initialize();

	// ステージを返す関数
	std::vector<PackedCell>& GetStage();

	// 指定した位置のセルを返す関数
	PackedCell GetCell(Vector2DInt pos) const;

	// 指定した位置にセルをセットする関数
	void SetCell(Vector2DInt pos, PackedCell cell);

	// コピーセルを返す関数
	std::unordered_map<Vector2DInt, PackedCell>& GetCopyCells();

	// コピーセルをセットする関数
	void SetCopyCells(std::unordered_map<Vector2DInt, PackedCell>& copyCells);

	// コピーセルを反転する関数
	void CopyInverse(bool isHorizontal);

	// カーソルの大きさを取得する関数
	Vector2DInt GetCursorSize() const { return m_cursorSize; }

	// カーソルの大きさをセットする関数
	void SetCursorSize(Vector2DInt size) { m_cursorSize = size; }

	// セルの数を返す関数
	int GetCellCount(CellTypes cell) { return m_cellCounter[cell]; }

	// セル情報を返す関数
	std::vector<Vector2DInt>& GetCellInfo(CellTypes t) { return m_cellsInfo[t]; }

	// セル情報をセットする関数
	void SetCellInfo(CellTypes t, std::vector<Vector2DInt>& info) { m_cellsInfo[t] = info; }

private:
	// セル情報を削除する関数
	bool DeleteCellInfo(CellTypes types, Vector2DInt pos);
};

