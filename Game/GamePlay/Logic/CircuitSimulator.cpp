#include "CircuitSimulator.h"

CircuitSimulator::CircuitSimulator(std::vector<PackedCell>& cells, std::vector<PackedCell>& nextCells)
	: m_cells{ cells }
	, m_nextCells{ nextCells }
	, m_devCells{ nullptr }
	, m_devNextCells{ nullptr }
	, m_generationNum{ 0 }
{
	size_t size = STAGE_HEIGHT * STAGE_WIDTH * sizeof(PackedCell);
}

void CircuitSimulator::Initialize()
{
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
	bool same = UpdateOnCPU(m_devCells, m_devNextCells);

	m_generationNum++;

	std::swap(m_cells, m_nextCells);

	return same;
}

bool CircuitSimulator::UpdateOnCPU(PackedCell* devCells, PackedCell* devNextCells)
{
	bool isSame = true;

	for(int i = 0; i < m_cells.size(); i++)
	{
		int index = i;
		int x = i % STAGE_WIDTH;
		int y = i / STAGE_WIDTH;

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
		PackedCell nC = 0;
		int t = (cNow >> 4) & 0b00001111;

		SetType(nC, GetType(cNow));
		SetSubType(nC, GetSubType(cNow));

		bool signal = false;

		switch (GetType(cNow))
		{
		case TYPE_WIRE:

			aroundLeft = (GetLeftSignal(cRight));   // 右セルが左向き信号
			aroundRight = (GetRightSignal(cLeft));  // 左セルが右向き
			aroundDown = (GetUpSignal(cDown));     // 下セルが上向き
			aroundUp = (GetDownSignal(cUp));   // 上セルが下向き

			switch (GetSubType(cNow))
			{
			case SUBTYPE_NORMAL:
			case SUBTYPE_LIGHT:

				// 信号を受け取るかどうか
				if (aroundDown || aroundUp || aroundLeft || aroundRight)
				{
					// ループ防止処理
					SetUpSignal(nC, !GetDownSignal(cUp));
					SetDownSignal(nC, !GetUpSignal(cDown));
					SetRightSignal(nC, !GetLeftSignal(cRight));
					SetLeftSignal(nC, !GetRightSignal(cLeft));
				}
				else
				{
					// ループ防止処理
					SetUpSignal(nC, false);
					SetDownSignal(nC, false);
					SetRightSignal(nC, false);
					SetLeftSignal(nC, false);
				}

				break;

			case SUBTYPE_CROSS:

				// 信号チェック
				SetUpSignal(nC, (aroundUp || aroundDown) && !GetDownSignal(cUp));
				SetDownSignal(nC, (aroundUp || aroundDown) && !GetUpSignal(cDown));
				SetRightSignal(nC, (aroundLeft || aroundRight) && !GetLeftSignal(cRight));
				SetLeftSignal(nC, (aroundLeft || aroundRight) && !GetRightSignal(cLeft));

				break;

			default:
				break;
			}

			break;

		case TYPE_OTHERS:

			if(GetSubType(cNow) == SUBTYPE_OUTPUT)
			{
				aroundLeft = (GetLeftSignal(cRight));   // 右セルが左向き信号
				aroundRight = (GetRightSignal(cLeft));  // 左セルが右向き
				aroundDown = (GetUpSignal(cDown));     // 下セルが上向き
				aroundUp = (GetDownSignal(cUp));   // 上セルが下向き

				// 信号を受け取るかどうか
				if (aroundDown || aroundUp || aroundLeft || aroundRight)
				{
					// ループ防止処理
					SetUpSignal(nC, !GetDownSignal(cUp));
					SetDownSignal(nC, !GetUpSignal(cDown));
					SetRightSignal(nC, !GetLeftSignal(cRight));
					SetLeftSignal(nC, !GetRightSignal(cLeft));
				}
				else
				{
					// ループ防止処理
					SetUpSignal(nC, false);
					SetDownSignal(nC, false);
					SetRightSignal(nC, false);
					SetLeftSignal(nC, false);
				}
			}
			else
			{
				nC = cNow;
			}
			break;

		case TYPE_INPUT:

			switch (GetSubType(cNow))
			{
				// アンドセルの場合
			case SUBTYPE_AND:

				aroundUp = (GetType(cUp) == TYPE_WIRE ? GetDownSignal(cUp) : true);
				aroundDown = (GetType(cDown) == TYPE_WIRE ? GetUpSignal(cDown) : true);
				aroundRight = (GetType(cRight) == TYPE_WIRE ? GetLeftSignal(cRight) : true);
				aroundLeft = (GetType(cLeft) == TYPE_WIRE ? GetRightSignal(cLeft) : true);

				signal = ((aroundUp && aroundDown) && (aroundLeft && aroundRight));

				break;
			case SUBTYPE_OR:

				aroundUp = (GetType(cUp) == TYPE_WIRE ? GetDownSignal(cUp) : false);
				aroundDown = (GetType(cDown) == TYPE_WIRE ? GetUpSignal(cDown) : false);
				aroundRight = (GetType(cRight) == TYPE_WIRE ? GetLeftSignal(cRight) : false);
				aroundLeft = (GetType(cLeft) == TYPE_WIRE ? GetRightSignal(cLeft) : false);

				signal = ((aroundUp || aroundDown) || (aroundLeft || aroundRight));

				break;
			case SUBTYPE_BUTTON:

				signal = false;
				SetUpSignal(nC, GetUpSignal(cNow));
				SetLeftSignal(nC, GetLeftSignal(cNow));
				SetDownSignal(nC, GetDownSignal(cNow));
				SetRightSignal(nC, GetRightSignal(cNow));

				break;
			default:
				break;
			}

			// 信号チェック
			if (signal)
			{
				SetUpSignal(nC, GetType(cUp) == TYPE_OUTPUT);
				SetDownSignal(nC, GetType(cDown) == TYPE_OUTPUT);
				SetRightSignal(nC, GetType(cRight) == TYPE_OUTPUT);
				SetLeftSignal(nC, GetType(cLeft) == TYPE_OUTPUT);
			}

			break;
		case TYPE_OUTPUT:

			aroundUp = (GetType(cUp) == TYPE_INPUT && GetDownSignal(cUp));
			aroundDown = (GetType(cDown) == TYPE_INPUT && GetUpSignal(cDown));
			aroundRight = (GetType(cRight) == TYPE_INPUT && GetLeftSignal(cRight));
			aroundLeft = (GetType(cLeft) == TYPE_INPUT && GetRightSignal(cLeft));

			switch (GetSubType(cNow))
			{
			case SUBTYPE_NORMAL:
				signal = ((aroundUp || aroundDown) || (aroundLeft || aroundRight));
				break;
			case SUBTYPE_NOT:
				signal = !((aroundUp || aroundDown) || (aroundLeft || aroundRight));
				break;
			default:
				break;
			}

			if (signal)
			{
				SetUpSignal(nC, GetType(cUp) == TYPE_WIRE);
				SetDownSignal(nC, GetType(cDown) == TYPE_WIRE);
				SetRightSignal(nC, GetType(cRight) == TYPE_WIRE);
				SetLeftSignal(nC, GetType(cLeft) == TYPE_WIRE);
			}

			break;
		default:
			break;
		}

		if (m_nextCells[index] != nC)
		{
			isSame = false;
		}
		// コピー
		m_nextCells[index] = nC;
	}

	return isSame;
}

PackedCell CircuitSimulator::getCellSafe(std::vector<PackedCell>& cells, int x, int y)
{
	if (x < 0 || x >= STAGE_WIDTH || y < 0 || y >= STAGE_HEIGHT) return 0b00000000;
	return cells[y * STAGE_WIDTH + x];
}
