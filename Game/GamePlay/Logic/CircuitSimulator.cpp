#include "CircuitSimulator.h"
#include "../Game/Common/ThreadPool.h"

CircuitSimulator::CircuitSimulator(std::vector<PackedCell>& cells, std::vector<PackedCell>& nextCells)
	: m_cells{ cells }
	, m_nextCells{ nextCells }
	, m_devCells{ nullptr }
	, m_devNextCells{ nullptr }
	, m_generationNum{ 0 }
	, m_isSame{ false }
	, m_tasks{}
{
	size_t size = STAGE_HEIGHT * STAGE_WIDTH * sizeof(PackedCell);
}

void CircuitSimulator::Initialize()
{
	// 分割数を決定
	int divNum = (ThreadPool::GetInstance().GetThreadCount() / 2 < STAGE_WIDTH ? ThreadPool::GetInstance().GetThreadCount() / 2 : STAGE_WIDTH);

	m_tasks.resize(divNum);
}

void CircuitSimulator::Update(Vector2D cameraPos, float cameraScale)
{
	if(MouseDown() & MOUSE_INPUT_LEFT) 
	{
		int index = GetIndex(GetCellIndex(m_mousePos, cameraPos, cameraScale).x, GetCellIndex(m_mousePos, cameraPos, cameraScale).y);

		if(GetType(m_cells[index]) == TYPE_INPUT && GetSubType(m_cells[index]) == SUBTYPE_BUTTON)
		{
			SetUpSignal(m_cells[index], !GetUpSignal(m_cells[index]));
			SetDownSignal(m_cells[index], !GetDownSignal(m_cells[index]));
			SetRightSignal(m_cells[index], !GetRightSignal(m_cells[index]));
			SetLeftSignal(m_cells[index], !GetLeftSignal(m_cells[index]));
		}
	}
}

bool CircuitSimulator::ToNextCells()
{
	m_isSame = true;

	UpdateOnCPU();

	m_generationNum++;

	std::swap(m_cells, m_nextCells);

	return m_isSame;
}

bool CircuitSimulator::UpdateOnCPU()
{
	for(int i = 0; i < m_tasks.size(); i++)
	{
		int left = i * (STAGE_WIDTH / m_tasks.size()) - OFFSET_X;
		int right = (i == m_tasks.size() - 1 ? OFFSET_X + 1 : (i + 1) * (STAGE_WIDTH / m_tasks.size()) - OFFSET_X);

		// タスクを追加
		m_tasks[i] = ThreadPool::GetInstance().AddTask(
			// ラムダ式に丸める
			[this](int minX, int minY, int maxX, int maxY)
			{
				ToNextCellsOnThread(minX, minY, maxX, maxY);
			},
			left, -OFFSET_Y, right, OFFSET_Y + 1
		);
	}

	// 全スレッド実行終了を待機
	for (int i = 0; i < m_tasks.size(); i++)
	{
		m_tasks[i].get();
	}

	return m_isSame;
}

PackedCell CircuitSimulator::getCellSafe(std::vector<PackedCell>& cells, int x, int y)
{
	if (x < 0 || x >= STAGE_WIDTH || y < 0 || y >= STAGE_HEIGHT) return 0b00000000;
	return cells[y * STAGE_WIDTH + x];
}

void CircuitSimulator::ToNextCellsOnThread(int minX, int minY, int maxX, int maxY)
{
	for(int i = minY; i < maxY; i++)
	{
		for(int j = minX; j < maxX; j++)
		{
			int index = GetIndex(j, i);
			int x = j + OFFSET_X;
			int y = i + OFFSET_Y;

			if (index >= m_cells.size() || index < 0) continue;

			// 信号
			bool aroundUp = false, aroundDown = false, aroundLeft = false, aroundRight = false;

			PackedCell cNow = m_cells[index];

			if (cNow == 0)
			{
				m_nextCells[index] = 0;
				continue;
			}

			// 隣接セル
			PackedCell cUp = getCellSafe(m_cells, x, y - 1);
			PackedCell cDown = getCellSafe(m_cells, x, y + 1);
			PackedCell cLeft = getCellSafe(m_cells, x - 1, y);
			PackedCell cRight = getCellSafe(m_cells, x + 1, y);

			// 変換後のセル
			PackedCell nC = cNow;

			bool signal = false;

			int type = (GetType(cNow) << 2) | (GetSubType(cNow));

			switch (type)
			{
			case 0b0101:
			case 0b0111:
			case 0b0011:

				aroundLeft = (GetLeftSignal(cRight));   // 右セルが左向き信号
				aroundRight = (GetRightSignal(cLeft));  // 左セルが右向き
				aroundDown = (GetUpSignal(cDown));     // 下セルが上向き
				aroundUp = (GetDownSignal(cUp));   // 上セルが下向き

				// 信号を受け取るかどうか
				signal = aroundDown || aroundUp || aroundLeft || aroundRight;

				// ループ防止処理
				SetUpSignal(nC, signal && !GetDownSignal(cUp));
				SetDownSignal(nC, signal && !GetUpSignal(cDown));
				SetRightSignal(nC, signal && !GetLeftSignal(cRight));
				SetLeftSignal(nC, signal && !GetRightSignal(cLeft));

				break;

			case 0b0110:

				aroundLeft = (GetLeftSignal(cRight));   // 右セルが左向き信号
				aroundRight = (GetRightSignal(cLeft));  // 左セルが右向き
				aroundDown = (GetUpSignal(cDown));     // 下セルが上向き
				aroundUp = (GetDownSignal(cUp));   // 上セルが下向き

				// 信号チェック
				SetUpSignal(nC, (aroundUp || aroundDown) && !GetDownSignal(cUp));
				SetDownSignal(nC, (aroundUp || aroundDown) && !GetUpSignal(cDown));
				SetRightSignal(nC, (aroundLeft || aroundRight) && !GetLeftSignal(cRight));
				SetLeftSignal(nC, (aroundLeft || aroundRight) && !GetRightSignal(cLeft));

				break;

			case 0b1001:

				aroundUp = (GetType(cUp) == TYPE_WIRE ? GetDownSignal(cUp) : true);
				aroundDown = (GetType(cDown) == TYPE_WIRE ? GetUpSignal(cDown) : true);
				aroundRight = (GetType(cRight) == TYPE_WIRE ? GetLeftSignal(cRight) : true);
				aroundLeft = (GetType(cLeft) == TYPE_WIRE ? GetRightSignal(cLeft) : true);

				signal = ((aroundUp && aroundDown) && (aroundLeft && aroundRight));

				// 信号チェック
				SetUpSignal(nC, signal && GetType(cUp) == TYPE_OUTPUT);
				SetDownSignal(nC, signal && GetType(cDown) == TYPE_OUTPUT);
				SetRightSignal(nC, signal && GetType(cRight) == TYPE_OUTPUT);
				SetLeftSignal(nC, signal && GetType(cLeft) == TYPE_OUTPUT);

				break;

			case 0b1010:

				aroundUp = (GetType(cUp) == TYPE_WIRE ? GetDownSignal(cUp) : false);
				aroundDown = (GetType(cDown) == TYPE_WIRE ? GetUpSignal(cDown) : false);
				aroundRight = (GetType(cRight) == TYPE_WIRE ? GetLeftSignal(cRight) : false);
				aroundLeft = (GetType(cLeft) == TYPE_WIRE ? GetRightSignal(cLeft) : false);

				signal = ((aroundUp || aroundDown) || (aroundLeft || aroundRight));

				// 信号チェック
				SetUpSignal(nC, signal && GetType(cUp) == TYPE_OUTPUT);
				SetDownSignal(nC, signal && GetType(cDown) == TYPE_OUTPUT);
				SetRightSignal(nC, signal && GetType(cRight) == TYPE_OUTPUT);
				SetLeftSignal(nC, signal && GetType(cLeft) == TYPE_OUTPUT);

				break;

			case 0b1101:

				aroundUp = (GetType(cUp) == TYPE_INPUT && GetDownSignal(cUp));
				aroundDown = (GetType(cDown) == TYPE_INPUT && GetUpSignal(cDown));
				aroundRight = (GetType(cRight) == TYPE_INPUT && GetLeftSignal(cRight));
				aroundLeft = (GetType(cLeft) == TYPE_INPUT && GetRightSignal(cLeft));

				signal = ((aroundUp || aroundDown) || (aroundLeft || aroundRight));

				// 信号チェック
				SetUpSignal(nC, signal && GetType(cUp) == TYPE_WIRE);
				SetDownSignal(nC, signal && GetType(cDown) == TYPE_WIRE);
				SetRightSignal(nC, signal && GetType(cRight) == TYPE_WIRE);
				SetLeftSignal(nC, signal && GetType(cLeft) == TYPE_WIRE);

				break;

			case 0b1110:

				aroundUp = (GetType(cUp) == TYPE_INPUT && GetDownSignal(cUp));
				aroundDown = (GetType(cDown) == TYPE_INPUT && GetUpSignal(cDown));
				aroundRight = (GetType(cRight) == TYPE_INPUT && GetLeftSignal(cRight));
				aroundLeft = (GetType(cLeft) == TYPE_INPUT && GetRightSignal(cLeft));

				signal = !((aroundUp || aroundDown) || (aroundLeft || aroundRight));

				// 信号チェック
				SetUpSignal(nC, signal && GetType(cUp) == TYPE_WIRE);
				SetDownSignal(nC, signal && GetType(cDown) == TYPE_WIRE);
				SetRightSignal(nC, signal && GetType(cRight) == TYPE_WIRE);
				SetLeftSignal(nC, signal && GetType(cLeft) == TYPE_WIRE);

				break;

			default:
				break;
			}

			if (m_nextCells[index] != nC)
			{
				m_isSame = false;
			}

			// コピー
			m_nextCells[index] = nC;
		}
	}
}
