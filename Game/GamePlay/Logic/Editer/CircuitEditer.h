#pragma once
#include "StageReceiver.h"
#include "CommandManager.h"

#include "Commands/Commands.h"

#include "../CellInfo.h"
#include "SelectUI.h"

class CircuitEditer
{
public:
	enum class PutMode
	{
		None,
		Put,
		Copy,
		Paste,
		Range,
	};

private:

	// ステージの参照
	std::vector<PackedCell>& m_cells;

	// カメラの参照
	Vector2D& m_cameraPos;
	float& m_cameraScale;

	Vector2DInt m_downMousePos;
	Vector2DInt m_upMousePos;

	// マウスのインデックス
	Vector2DInt m_mouseIndex;

	// 設置モード
	PutMode m_nowPutMode;

	// レシーバー
	StageReceiver m_stageReceiver;

	//　コマンドマネージャー
	CommandManager m_commandManager;

	// 設置セル
	PackedCell m_putCell;

	// スタートフラグ
	bool m_isStart;

	// UI
	SelectUI m_selectUI;

public:
	CircuitEditer(std::vector<PackedCell>& stage, Vector2D& cameraPos, float& cameraScale);

	// 初期化
	void Initialize(PlayMode playMode);

	void Update(float elapsedTime);

	void CellUpdate();

	void Render();

	void Finalize();

	// 設置タイプ切り替え
	void ChangePutCell(PackedCell type) { m_putCell = type; };
	void ChangePutMode(PutMode putmode) { 
		m_nowPutMode = putmode;

		m_stageReceiver.SetCursorSize({ 1, 1 });
	}

	// UIの状態変更
	void ChangeUIState(State state) { m_selectUI.SetState(state); }

	// リセット
	void Reset();


	// セーブ
	void SaveCells(std::wstring fileName);
	// ロード
	void LoadCells(std::wstring fileName);

	// 反転
	void CopyInversion(bool horizontal);

	// 一手戻る
	void Undo();

	// 一手進める
	void Redo();

	// 各セルの数を返す関数
	int GetCellCount(std::pair<CellType, CellSubType> cell) { return m_stageReceiver.GetCellCount(cell); }

	// 各セルの情報を返す関数
	std::vector<Vector2DInt>& GetCellInfo(std::pair<CellType, CellSubType> cell) { return m_stageReceiver.GetCellInfo(cell); }

	// 各セルの情報をセットする関数
	void SetCellInfo(std::pair<CellType, CellSubType> cell, std::vector<Vector2DInt>& info) { m_stageReceiver.SetCellInfo(cell, info); }

	// ポイントがUIにあるか返す関数
	bool PointIsOnUI(Vector2D pos) { return m_selectUI.GetInSelectUI({ static_cast<int>(pos.x), static_cast<int>(pos.y)}); }

private:
	void PutUpdate();

	void CopyUpdate();

	void PasteUpdate();

	void RangeUpdate();

	void PasteRander();
};

