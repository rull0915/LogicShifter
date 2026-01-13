#pragma once

#include "Logic/CellInfo.h"
#include "../Game/Common/UI/Button.h"

// マネージャー基底クラス
class ModeManager
{
	// ----- メンバ変数宣言 ----- //
protected:

	// カメラ
	Vector2D m_cameraPos;
	float m_cameraScale;

	// スケールの限界値
	float m_minScale = 0;
	float m_maxScale = 50;

	// ステージ
	std::vector<PackedCell> m_cells;
	std::vector<PackedCell> m_nextCells;

	// ------- 関数宣言 ------- //
public:
	// コンストラクタ
	ModeManager();

	// 純粋仮想関数
	virtual void Initialize() = 0;

	virtual void Update(float elapsedTime) = 0;

	virtual void Render() = 0;

	virtual void Finalize() = 0;

protected:
	// その他関数
	
	// グリッドの描画
	void GridRender();

	// セルの描画
	void CellRender();

	// 境界線の描画
	void BorderRender();

	// スケール変化
	void ChangeScale(float newScale);
};

