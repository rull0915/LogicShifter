#include "BlocksTransition.h"

BlocksTransition::BlocksTransition(float transTime, Transition::Mode mode, int blocksColor, Vector2D startPos, Vector2DInt divNum)
	: SceneTransition(transTime, mode)
	, m_blocksColor{ blocksColor }
	, m_startPos{ startPos }
	, m_divisionNum{ divNum }
	, m_blockMap{}
	, m_maxNum{ -1 }
	, m_canDrawNum{ 0 }
{
}

void BlocksTransition::Initialize()
{
	if (m_divisionNum.x <= 0) m_divisionNum.x = 1;
	if (m_divisionNum.y <= 0) m_divisionNum.y = 1;

	// ブロックマップ初期化
	m_blockMap.resize(m_divisionNum.y);
	for(auto& coll : m_blockMap)
	{
		coll.resize(m_divisionNum.x);
		for (auto& cell : coll) cell = INT_MAX;
	}

	// 開始地点が所属するブロックを探索
	Vector2DInt startPos = { m_startPos.x / (Screen::WIDTH / m_divisionNum.x), m_startPos.y / (Screen::HEIGHT / m_divisionNum.y) };

	if (startPos.x >= m_divisionNum.x) startPos.x = m_divisionNum.x - 1;
	if (startPos.y >= m_divisionNum.y) startPos.y = m_divisionNum.y - 1;

	// 探索の開始地点を決定
	m_blockMap[startPos.y][startPos.x] = 0;

	// 探索の開始
	while (true)
	{
		bool change = false;

		for(int i = 0; i < m_divisionNum.y; i++)
		{
			for(int j = 0; j < m_divisionNum.x; j++)
			{
				// 既に割り当てられているセルなら
				if(m_blockMap[i][j] != INT_MAX)
				{
					// 上
					if (i - 1 >= 0 && m_blockMap[i - 1][j] > m_blockMap[i][j] + 1)
					{
						m_blockMap[i - 1][j] = m_blockMap[i][j] + 1;
						change = true;
					}
					// 下
					if (i + 1 < m_divisionNum.y && m_blockMap[i + 1][j] > m_blockMap[i][j] + 1)
					{
						m_blockMap[i + 1][j] = m_blockMap[i][j] + 1;
						change = true;
					}
					// 左
					if (j - 1 >= 0 && m_blockMap[i][j - 1] > m_blockMap[i][j] + 1)
					{
						m_blockMap[i][j - 1] = m_blockMap[i][j] + 1;
						change = true;
					}
					// 右
					if (j + 1 < m_divisionNum.x && m_blockMap[i][j + 1] > m_blockMap[i][j] + 1)
					{
						m_blockMap[i][j + 1] = m_blockMap[i][j] + 1;
						change = true;
					}
				}
			}
		}

		if (!change) break;
	}

	// 最大地を取得
	for (int i = 0; i < m_divisionNum.y; i++)
	{
		for (int j = 0; j < m_divisionNum.x; j++)
		{
			if (m_blockMap[i][j] > m_maxNum) m_maxNum = m_blockMap[i][j];
		}
	}
}

bool BlocksTransition::Update(float elapsedTime)
{
	// 経過時間の加算
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_transSec) m_elapsedTime = m_transSec;

	m_canDrawNum = static_cast<int>((m_maxNum + 1) * (m_elapsedTime / m_transSec));

	// 遷移時間を超えたかどうか
	return (m_elapsedTime >= m_transSec);
}

void BlocksTransition::Render()
{
	Vector2D blockSize = { Screen::WIDTH / m_divisionNum.x, Screen::HEIGHT / m_divisionNum.y };

	for (int i = 0; i < m_divisionNum.y; i++)
	{
		for (int j = 0; j < m_divisionNum.x; j++)
		{
			switch (m_mode)
			{
			case Transition::Mode::In:
				if (m_blockMap[i][j] <= m_canDrawNum)
				{
					DrawBox(blockSize.x * j, blockSize.y * i, blockSize.x * (j + 1), blockSize.y * (i + 1), m_blocksColor, true);
				}
				break;
			case Transition::Mode::Out:
				if (m_blockMap[i][j] >= m_canDrawNum)
				{
					DrawBox(blockSize.x * j, blockSize.y * i, blockSize.x * (j + 1), blockSize.y * (i + 1), m_blocksColor, true);
				}
				break;
			default:
				break;
			}
		}
	}
}
