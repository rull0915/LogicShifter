#include "ModeManager.h"

ModeManager::ModeManager()
	: m_cells{}
	, m_nextCells{}
	, m_cameraPos{ Screen::WIDTH / 2, Screen::HEIGHT / 2 }
	, m_cameraScale{ 1 }
	, m_resetButton{ {Screen::WIDTH / 2 - 50, 50}, {75, 75}, true, m_ghIcons["Reset"]}
{
}

void ModeManager::GridRender()
{
	float scale = (1.0f / m_cameraScale);
	const float blockPixel = (BLOCK_SIZE * scale);

	// カメラの左上がどのセルかを求める
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * scale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * scale;

	int startCellX = (0 + m_cameraPos.x - offsetX) / (blockPixel)-1;
	int startCellY = (0 + m_cameraPos.y - offsetY) / (blockPixel)-1;

	// 画面に何マス描けば十分か
	int cellCountX = Screen::WIDTH / blockPixel + 2;
	int cellCountY = Screen::HEIGHT / blockPixel + 2;

	// 方眼線の色（半透明っぽく）
	int gridColor = 0;

	// 縦線を描画
	for (int i = 0; i <= cellCountX; i++)
	{
		if ((startCellX + i) % 5 == 0)
		{
			if (blockPixel < 8) continue;
			gridColor = GetColor(200, 200, 200);
		}
		else
		{
			if (blockPixel < 15) continue;
			gridColor = GetColor(100, 100, 100);
		}

		int x = (startCellX + i) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX;

		DrawLine(x, 0, x, Screen::HEIGHT, gridColor);
	}

	// 横線を描画
	for (int j = 0; j <= cellCountY; j++)
	{
		if ((startCellY + j) % 5 == 0)
		{
			if (blockPixel < 8) continue;
			gridColor = GetColor(200, 200, 200);
		}
		else
		{
			if (blockPixel < 15) continue;
			gridColor = GetColor(100, 100, 100);
		}

		int y = (startCellY + j) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY;

		DrawLine(0, y, Screen::WIDTH, y, gridColor);
	}
}

void ModeManager::CellRender()
{
	float scale = (1.0f / m_cameraScale);

	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * scale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * scale;

	// セルの描画
	// スクリーン内のセルを計算
	Vector2DInt min = GetCellIndex({ 0, 0 }, m_cameraPos, scale);
	Vector2DInt max = GetCellIndex({ Screen::WIDTH, Screen::HEIGHT }, m_cameraPos, scale);

	for (int i = min.y; i <= max.y; i++)
	{
		for (int j = min.x; j <= max.x; j++)
		{
			// 範囲外チェック
			if ((j < -OFFSET_X || j >= STAGE_WIDTH - OFFSET_X) || (i < -OFFSET_Y || i >= STAGE_HEIGHT - OFFSET_Y)) continue;

			PackedCell c = m_cells[GetIndex(j, i)];

			int type = GetType(c), subType = GetSubType(c);
			if (type == TYPE_OTHERS && subType == SUBTYPE_NONE) continue;

			int color = Cell::COLORS[{type, subType}];

			if (c & 0b00001111) color = Cell::ON_SIGNAL_COLORS[{type, subType}];

			// 描画
			DrawBox(
				(j) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
				(i) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
				(j + 1) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
				(i + 1) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
				color,
				true
			);
		}
	}
}

void ModeManager::BorderRender()
{
	float scale = (1.0f / m_cameraScale);

	// カメラの左上がどのセルかを求める
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * scale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * scale;


	// 境界線の表示
	DrawLine(
		(-OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(-OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		(-OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(STAGE_HEIGHT - OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		0xffffff,
		5
	);
	DrawLine(
		(-OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(-OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		(STAGE_WIDTH - OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(-OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		0xffffff,
		5
	);
	DrawLine(
		(STAGE_WIDTH - OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(STAGE_HEIGHT - OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		(-OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(STAGE_HEIGHT - OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		0xffffff,
		5
	);
	DrawLine(
		(STAGE_WIDTH - OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(STAGE_HEIGHT - OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		(STAGE_WIDTH - OFFSET_X) * (BLOCK_SIZE * scale) - m_cameraPos.x + offsetX,
		(-OFFSET_Y) * (BLOCK_SIZE * scale) - m_cameraPos.y + offsetY,
		0xffffff,
		5
	);
}

void ModeManager::ChangeScale(float newScale)
{
	if (newScale < m_minScale || newScale > m_maxScale) return;

	float prevScale = m_cameraScale;
	m_cameraScale = newScale;

	// カメラ補正
	m_cameraPos.x = (m_cameraPos.x) * (prevScale / newScale);
	m_cameraPos.y = (m_cameraPos.y) * (prevScale / newScale);
}
