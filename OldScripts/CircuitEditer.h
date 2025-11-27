#pragma once
#include "../CellInfo.h"
#include "SelectUI.h"

enum class PutMode
{
	None,
	Put,
	Copy,
	Paste,
	Range,
};

struct SaveCell
{
	int pos;

	PackedCell before;
	PackedCell after;
};

class CircuitEditer
{
private:
	// ステージの参照
	std::vector<PackedCell>& m_cells;

	// 設置モード
	PutMode m_nowPutMode;
	// 設置セル
	std::pair<CellType, CellSubType> m_nowPutType;

	// カーソルのサイズ
	Vector2DInt m_cursorSize;

	// 選択フラグ
	bool m_selectionStart;
	// 範囲選択の位置
	std::pair<Vector2DInt, Vector2DInt> m_selectionPos;

	// 置ける状況かどうか
	bool m_canPut;

	// コピーフラグ
	bool m_copyStart;
	// コピー範囲
	std::pair<Vector2DInt, Vector2DInt> m_copyPos;
	// コピーしたセル
	std::unordered_map<Vector2DInt, PackedCell> m_copyCells;

	// セル設置の記憶用
	std::vector<std::vector<SaveCell>> m_saveCells;

	// UI
//	SelectUI m_selectUi;

	// 各セルの数
	std::map<std::pair<CellType, CellSubType>, int> m_cellsCount;

public:
	// コンストラクタ
	CircuitEditer(std::vector<PackedCell>& cells);

	// 初期化
	void Initialize(PlayMode playMode);

	// 更新
	void Update(float elapsedTime);

	// 描画
	void Render(Vector2D cameraPos, float scale);

	// 生存セルを置く関数
	void PutCell(Vector2DInt mousePos, Vector2D cameraPos, float scale);

	// コピー範囲を決める
	void DecideCell(Vector2DInt mousePos, Vector2D cameraPos, float scale);

	// セルを削除
	void DeleteCell(Vector2DInt mousePos, Vector2D cameraPos, float scale);

	// クリックされたときの関数
	void Push(Vector2DInt mousePos, Vector2D cameraPos, float scale);

	// リセット
	void Reset();

	// 設置タイプ切り替え
	void ChangePutType(std::pair<CellType, CellSubType> type) { m_nowPutType = type; };
	void ChangePutMode(PutMode putmode) { m_nowPutMode = putmode; if (putmode == PutMode::Put) m_cursorSize = { 1, 1 }; }

	// UIの状態変更
//	void ChangeUIState(State state) { m_selectUi.SetState(state); }

	// セーブ
	void SaveCells(std::wstring fileName);
	// ロード
	void LoadCells(std::wstring fileName);

	// 反転
	void CopyInversion(bool horizontal);

	// 一手戻る
	void Undo();

	// 各セルの数を返す関数
	int GetCellCount(std::pair<CellType, CellSubType>);

//	bool PointIsOnUI(Vector2D pos) { return m_selectUi.GetInSelectUI({static_cast<int>(pos.x), static_cast<int>(pos.y)}); }

private:
	// カーソル描画
	void CursorRender(Vector2DInt mousePos, Vector2D cameraPos, float scale);
};

