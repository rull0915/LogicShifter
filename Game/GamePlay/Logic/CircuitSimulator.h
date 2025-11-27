#pragma once
#include "CellInfo.h"

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

public:
	CircuitSimulator(std::vector<PackedCell>& cells, std::vector<PackedCell>& nextCells);
	~CircuitSimulator() {
	}

	void Initialize();

	void Update(Vector2D cameraPos, float cameraScale);

	bool ToNextCells();

	bool UpdateOnCPU(PackedCell* devCells, PackedCell* devNextCells);

	void ResetGenerationNum() { m_generationNum = 0; }

	int GetGenerationNum() const { return m_generationNum; }

private:
	PackedCell getCellSafe(std::vector<PackedCell>& cells, int x, int y);
};

