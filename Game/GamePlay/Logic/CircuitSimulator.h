#pragma once
#include "CellInfo.h"
#include <condition_variable>
#include <future>

class CircuitSimulator
{
	// ステージの参照
	std::vector<PackedCell>& m_cells;
	std::vector<PackedCell>& m_nextCells;

	// GPU用
	PackedCell* m_devCells;
	PackedCell* m_devNextCells;

	// 世代数
	int m_generationNum;

	// 同じかどうかのフラグ
	bool m_isSame;

	// 分割実行用
	std::vector<std::future<void>> m_tasks;

public:
	CircuitSimulator(std::vector<PackedCell>& cells, std::vector<PackedCell>& nextCells);
	~CircuitSimulator() {
	}

	void Initialize();

	void Update(Vector2D cameraPos, float cameraScale);

	bool ToNextCells();

	bool UpdateOnCPU();

	void ResetGenerationNum() { m_generationNum = 0; }

	int GetGenerationNum() const { return m_generationNum; }

private:
	inline PackedCell getCellSafe(std::vector<PackedCell>& cells, int x, int y);

	void ToNextCellsOnThread(int minX, int minY, int maxX, int maxY);
};

