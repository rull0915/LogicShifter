#pragma once
#include "SceneTransition.h"

class BlocksTransition : public SceneTransition
{
private:
	int m_blocksColor;

	Vector2D m_startPos;

	Vector2DInt m_divisionNum;

	std::vector<std::vector<int>> m_blockMap;

	int m_maxNum;

	// ï`âÊâ¬î\Ç»î‘çÜ
	int m_canDrawNum;

public:
	BlocksTransition(float transTime, Transition::Mode mode, int blocksColor = 0x000000, Vector2D startPos = { 0, 0 }, Vector2DInt divNum = {16, 9});

	void Initialize() override;

	bool Update(float elapsedTime) override;

	void Render() override;
};

