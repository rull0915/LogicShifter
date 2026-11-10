#include "CellRenderer.h"

void DrawCell(int indexX, int indexY, Vector2D cameraPos, float cameraScale, PackedCell cell)
{
	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * cameraScale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * cameraScale;

	int color = Cell::COLORS[{GetType(cell), GetSubType(cell)}];

	DrawBoxAA(
		indexX * (BLOCK_SIZE * cameraScale) - cameraPos.x + offsetX, 
		indexY * (BLOCK_SIZE * cameraScale) - cameraPos.y + offsetY, 
		(indexX + 1) * (BLOCK_SIZE * cameraScale) - cameraPos.x + offsetX, 
		(indexY + 1) * (BLOCK_SIZE * cameraScale) - cameraPos.y + offsetY, 
		color, 
		true);
}

void DrawStringOnGrid(int indexX, int indexY, Vector2D cameraPos, float cameraScale, int color, const TCHAR* string)
{
	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * cameraScale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * cameraScale;

	MyDrawExtendFormatStringToHandleToCenter(
		indexX * (BLOCK_SIZE * cameraScale) - cameraPos.x + offsetX + (BLOCK_SIZE * cameraScale) / 2,
		indexY * (BLOCK_SIZE * cameraScale) - cameraPos.y + offsetY + (BLOCK_SIZE * cameraScale) / 2,
		cameraScale / 4,
		cameraScale / 4,
		color,
		GetFontHandle(128),
		string);
}

void RangeRender(Vector2DInt first, Vector2DInt second, Vector2D cameraPos, float cameraScale, int color)
{
	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * cameraScale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * cameraScale;

	DrawBoxAA((first.x) * (BLOCK_SIZE * cameraScale) - cameraPos.x + offsetX, 
		(first.y) * (BLOCK_SIZE * cameraScale) - cameraPos.y + offsetY, 
		(second.x + 1) * (BLOCK_SIZE * cameraScale) - cameraPos.x + offsetX, 
		(second.y + 1) * (BLOCK_SIZE * cameraScale) - cameraPos.y + offsetY, 
		color, false, 3);
}
