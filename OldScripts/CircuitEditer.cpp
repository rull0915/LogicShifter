#include "CircuitEditer.h"

CircuitEditer::CircuitEditer(std::vector<PackedCell>& cells)
	: m_cells{ cells }
	, m_nowPutMode{ PutMode::Put }
	, m_nowPutType{ TYPE_WIRE, SUBTYPE_NORMAL }
	, m_cursorSize{ 1, 1 }
	, m_selectionStart{ false }
	, m_selectionPos{ {0, 0}, {0, 0} }
	, m_canPut{ false }
	, m_copyStart{ false }
	, m_copyPos{ {0, 0}, {0, 0} }
	, m_copyCells{}
//	, m_selectUi{ this }
	, m_saveCells{}
	, m_cellsCount{}
{
}

void CircuitEditer::Initialize(PlayMode playMode)
{
//	m_selectUi.Initialize(playMode);
	m_nowPutType = { TYPE_WIRE, SUBTYPE_NORMAL };

	// カウントの初期化
	m_cellsCount.clear();

	for(auto cell : Cell::ALL_CELL)
	{
		m_cellsCount[cell] = 0;
	}
}

// 更新処理
void CircuitEditer::Update(float elapsedTime)
{
	// セーブを追加
	if(m_saveCells.size() == 0) m_saveCells.push_back({});

//	m_selectUi.Update(elapsedTime);

	// セーブに空白があれば削除
	for(int i = 0; i < m_saveCells.size() - 1; i++)
	{
		if(m_saveCells[i].size() == 0)
		{
			m_saveCells.erase(m_saveCells.begin() + i);
			break;
		}
	}

	// マウスを離したときに
	if (MouseUp() & MOUSE_INPUT_LEFT || MouseUp() & MOUSE_INPUT_RIGHT)
	{
		m_saveCells.push_back({});
	}
}

void CircuitEditer::Render(Vector2D cameraPos, float scale)
{			  
	// カーソルの描画
	CursorRender(m_mousePos, cameraPos, scale);

	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * scale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * scale;

	switch (m_nowPutMode)
	{
	case PutMode::Put:
		// カーソル描画
		break;
	case PutMode::Copy:
		if (m_copyStart)
		{
			// コピー範囲描画
			DrawBox(
				(m_copyPos.first.x) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
				(m_copyPos.first.y) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
				(m_copyPos.second.x + 1) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
				(m_copyPos.second.y + 1) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
				0x770000,
				false, 3
			);
		}
		break;
	case PutMode::Paste:

		// マウスのセル位置
		Vector2DInt pos = GetCellIndex(m_mousePos, cameraPos, scale);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		// プレビュー描画
		for (const auto& cell : m_copyCells)
		{
			int color = Cell::COLORS[{GetType(cell.second), GetSubType(cell.second)}];

			// 描画
			DrawBox(
				(cell.first.x + pos.x) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
				(cell.first.y + pos.y) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
				(cell.first.x + pos.x + 1) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
				(cell.first.y + pos.y + 1) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
				color,
				true
			);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;

	case PutMode::Range:

		if (m_selectionStart)
		{
			// 選択範囲描画
			DrawBox(
				(m_selectionPos.first.x) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
				(m_selectionPos.first.y) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
				(GetCellIndex(m_mousePos, cameraPos, scale).x + 1) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
				(GetCellIndex(m_mousePos, cameraPos, scale).y + 1) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
				0x770000,
				false, 3
			);
		}

		break;
	default:
		break;
	}

	// UIの描画
//	m_selectUi.Render();

	// テスト用
	int index = 0;
	for(auto test : m_cellsCount)
	{
		DrawFormatString(0, index * 20, 0xffffff, L"Type: %d SubType: %d Count: %d", test.first.first, test.first.second, test.second);

		index++;
	}
}

void CircuitEditer::PutCell(Vector2DInt mousePos, Vector2D cameraPos, float scale)
{
	if (!m_canPut) return;

	Vector2DInt cellPos = GetCellIndex(mousePos, cameraPos, scale);

	switch (m_nowPutMode)
	{
	case PutMode::Put:

		// カーソルの範囲分ループ
		for (int i = 0; i < m_cursorSize.y; i++)
		{
			for (int j = 0; j < m_cursorSize.x; j++)
			{
				// ステージ範囲外ならスキップ
				if (GetIndex(j, i) < 0 || GetIndex(j, i) >= m_cells.size()) continue;

				// 置くセルを作成
				PackedCell C = 0;

				// タイプを設定
				SetType(C, m_nowPutType.first);
				SetSubType(C, m_nowPutType.second);

				// 置こうとした位置に既にブロックがあればスキップ
				if (m_cells[GetIndex(cellPos.x - j, cellPos.y - i)] != 0) continue;

				if (m_cellsCount[m_nowPutType] >= Cell::CELL_MAX_COUNT[m_nowPutType]) return;

				// セーブ用の構造体を宣言
				SaveCell s;
				s.pos = GetIndex(cellPos.x - j, cellPos.y - i);
				s.before = m_cells[GetIndex(cellPos.x - j, cellPos.y - i)];

				// 更新
				m_cells[GetIndex(cellPos.x - j, cellPos.y - i)] = C;
				s.after = C;

				// カウンタのインクリメント
				m_cellsCount[m_nowPutType]++;

				// セーブの追加
				m_saveCells[m_saveCells.size() - 1].push_back(s);
			}
		}

		break;
	case PutMode::Copy:

		m_copyPos.second = cellPos;

		break;
	case PutMode::Paste:
		break;
	default:
		break;
	}
}

void CircuitEditer::DecideCell(Vector2DInt mousePos, Vector2D cameraPos, float scale)
{
	Vector2DInt cellPos = GetCellIndex(mousePos, cameraPos, scale);

	// UIとの被りチェック
//	if (m_selectUi.GetInSelectUI(mousePos)) return;

	// コピーの場合
	if (m_nowPutMode == PutMode::Copy && m_copyStart)
	{
		Vector2DInt min = m_copyPos.second, max = m_copyPos.first;

		m_copyPos.second = cellPos;

		m_copyCells.clear();

		for(int i = m_copyPos.first.y; i <= m_copyPos.second.y; i++)
		{
			for (int j = m_copyPos.first.x; j <= m_copyPos.second.x; j++)
			{
				if (GetIndex(j, i) < 0 || GetIndex(j, i) >= m_cells.size()) continue;

				if(GetType(m_cells[GetIndex(j, i)]) == TYPE_WIRE && GetSubType(m_cells[GetIndex(j, i)]) == SUBTYPE_NONE) continue;

				if (min.x > j) min.x = j;
				if (min.y > i) min.y = i;
				if (max.x < j) max.x = j;
				if (max.y < i) max.y = i;
			}
		}

		// 設置モードをリセット
		m_nowPutMode = PutMode::Put;
		m_copyStart = false;

		m_copyPos.first = min;
		m_copyPos.second = max;

		for (int i = m_copyPos.first.y; i <= m_copyPos.second.y; i++)
		{
			for (int j = m_copyPos.first.x; j <= m_copyPos.second.x; j++)
			{
				if (GetIndex(j, i) < 0 || GetIndex(j, i) >= m_cells.size()) continue;

				if (GetType(m_cells[GetIndex(j, i)]) == TYPE_WIRE && GetSubType(m_cells[GetIndex(j, i)]) == SUBTYPE_NONE) continue;

				// 左上基準のローカル座標
				m_copyCells[{j - m_copyPos.first.x, i - m_copyPos.first.y}] = m_cells[GetIndex(j, i)];
			}
		}
	}

	// 範囲選択の場合
	else if (m_nowPutMode == PutMode::Range && m_selectionStart)
	{
		// 選択範囲の右下
		m_selectionPos.second = { cellPos.x + 1, cellPos.y + 1 };

		// サイズ決定
		m_cursorSize = m_selectionPos.second - m_selectionPos.first;

		m_nowPutMode = PutMode::Put;

		m_selectionStart = false;
	}
}

void CircuitEditer::DeleteCell(Vector2DInt mousePos, Vector2D cameraPos, float scale)
{
	// UIとの被りチェック
//	if (m_selectUi.GetInSelectUI(mousePos)) return;

	if (MouseEnter() & MOUSE_INPUT_LEFT) return;

	Vector2DInt cellPos = GetCellIndex(mousePos, cameraPos, scale);

	for (int i = 0; i < m_cursorSize.y; i++)
	{
		for (int j = 0; j < m_cursorSize.x; j++)
		{
			if (GetIndex(j, i) < 0 || GetIndex(j, i) >= m_cells.size()) continue;
			// 既に何もなかったらスキップ
			if (m_cells[GetIndex(cellPos.x - j, cellPos.y - i)] == 0) continue;

			SaveCell s;
			s.pos = GetIndex(cellPos.x - j, cellPos.y - i);
			s.before = m_cells[GetIndex(cellPos.x - j, cellPos.y - i)];
			s.after = 0;

			// カウンタのデクリメント
			m_cellsCount[{GetType(m_cells[GetIndex(cellPos.x - j, cellPos.y - i)]), GetSubType(m_cells[GetIndex(cellPos.x - j, cellPos.y - i)])}]--;

			m_cells[GetIndex( cellPos.x - j, cellPos.y - i )] = 0;

			m_saveCells[m_saveCells.size() - 1].push_back(s);
		}
	}
}

void CircuitEditer::Push(Vector2DInt mousePos, Vector2D cameraPos, float scale)
{
	// UIとの被りチェック
//	m_canPut = !m_selectUi.GetInSelectUI(mousePos);

	// ズーム中心補正
	int x = GetCellIndex(mousePos, cameraPos, scale).x;
	int y = GetCellIndex(mousePos, cameraPos, scale).y;

	if (!m_canPut) return;

	if (GetIndex(x, y) < 0 || GetIndex(x, y) >= m_cells.size()) return;

	PackedCell c = m_cells[GetIndex(x, y)];

	switch (m_nowPutMode)
	{
	case PutMode::Put:

		if (GetType(c) == TYPE_INPUT && GetSubType(c) == SUBTYPE_BUTTON)
		{
			SetDownSignal	(c, !GetDownSignal(c));
			SetUpSignal		(c, !GetUpSignal(c));
			SetRightSignal	(c, !GetRightSignal(c));
			SetLeftSignal	(c, !GetLeftSignal(c));

			m_cells[GetIndex(x, y)] = c;
		}

		break;
	case PutMode::Copy:

		m_copyStart = true;
		m_copyPos.first = { x, y };

		break;
	case PutMode::Paste:

		for (auto cell : m_copyCells)
		{
			SaveCell s;

			s.pos = GetIndex(cell.first.x + x, cell.first.y + y);
			s.before = m_cells[GetIndex(cell.first.x + x, cell.first.y + y)];

			if (m_cells[GetIndex(cell.first.x + x, cell.first.y + y)] != 0)
			{
				m_cellsCount[{GetType(m_cells[GetIndex(cell.first.x + x, cell.first.y + y)])
							 ,GetSubType(m_cells[GetIndex(cell.first.x + x, cell.first.y + y)])}]--;
			}
			if (m_cellsCount[{GetType(cell.second), GetSubType(cell.second)}] >= Cell::CELL_MAX_COUNT[{GetType(cell.second), GetSubType(cell.second)}]) continue;

			m_cellsCount[{GetType(cell.second), GetSubType(cell.second)}]++;

			// コピー
			m_cells[GetIndex( cell.first.x + x,cell.first.y + y )] = cell.second;
		
			s.after = cell.second;

			m_saveCells[m_saveCells.size() - 1].push_back(s);
		}

	case PutMode::Range:

		// 選択範囲の左上を決定
		m_selectionPos.first = { x, y };

		m_selectionStart = true;

		break;

		break;
	default:
		break;
	}
}

void CircuitEditer::Reset()
{
	std::fill(m_cells.begin(), m_cells.end(), 0);

	for (auto cell : Cell::ALL_CELL)
	{
		m_cellsCount[cell] = 0;
	}
}

void CircuitEditer::CursorRender(Vector2DInt mousePos, Vector2D cameraPos, float scale)
{
	Vector2DInt cursorCell = GetCellIndex(mousePos, cameraPos, scale);

	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * scale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * scale;

	DrawBox(
		(cursorCell.x + 1) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
		(cursorCell.y + 1) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
		(cursorCell.x - m_cursorSize.x + 1) * (BLOCK_SIZE * scale) - cameraPos.x + offsetX,
		(cursorCell.y - m_cursorSize.y + 1) * (BLOCK_SIZE * scale) - cameraPos.y + offsetY,
		0xAAAAFf,
		false
	);
}

void CircuitEditer::SaveCells(std::wstring fileName)
{
	// ファイルへ書き込み
	std::ofstream file(fileName);

	if (file.is_open())
	{
		for(int i = 0; i < STAGE_HEIGHT; i++)
		{
			for(int j = 0; j < STAGE_WIDTH; j++)
			{
				if (m_cells[i * STAGE_WIDTH + j] == 0) continue;

				file << j - OFFSET_X << ',' << i - OFFSET_Y << ',' << (m_cells[i * STAGE_WIDTH + j] & 0b11110000) << '\n';
			}
		}
	}
}

void CircuitEditer::LoadCells(std::wstring fileName)
{
	// セルのリセット
	Reset();

	// ファイルから読み込み
	std::ifstream ifs(fileName);
	std::string line;

	PackedCell cell;
	Vector2DInt pos;

	while (std::getline(ifs, line))
	{
		std::istringstream iss(line);

		// カンマ区切りで分割する
		std::string item;

		getline(iss, item, ',');
		pos.x = std::stoi(item);

		getline(iss, item, ',');
		pos.y = std::stoi(item);

		// タイプ
		getline(iss, item, ',');
		cell = stoi(item);

		m_cellsCount[{GetType(cell), GetSubType(cell)}]++;

		m_cells[GetIndex(pos.x, pos.y)] = cell;
	}

	// ファイルをクローズ
	ifs.close();
}

// コピーセルの反転
void CircuitEditer::CopyInversion(bool horizontal)
{
	auto save = m_copyCells;

	m_copyCells.clear();

	for (auto cell : save)
	{
		Vector2DInt pos;
		if (horizontal)
		{
			pos = { (m_copyPos.second.x - m_copyPos.first.x) - cell.first.x, cell.first.y };
		}
		else
		{
			pos = { cell.first.x, (m_copyPos.second.y - m_copyPos.first.y) - cell.first.y };
		}
		m_copyCells[pos] = cell.second;
	}
}

void CircuitEditer::Undo()
{
	if (m_saveCells.size() <= 1) return;

	for(auto cell : m_saveCells[m_saveCells.size() - 2])
	{
		if (cell.before == 0) 
			 m_cellsCount[{GetType(m_cells[cell.pos]), GetSubType(m_cells[cell.pos])}]--;
		else m_cellsCount[{cell.before, cell.before}]++;

		m_cells[cell.pos] = cell.before;
	}

	m_saveCells.erase(m_saveCells.begin() + m_saveCells.size() - 2);
}

int CircuitEditer::GetCellCount(std::pair<CellType, CellSubType> cell)
{
	return m_cellsCount[cell];
}
