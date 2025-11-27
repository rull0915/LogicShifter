#pragma once

#include "CellInfo.h"

void DrawCell(int indexX, int indexY, Vector2D cameraPos, float cameraScale, PackedCell cell);

void DrawStringOnGrid(int indexX, int indexY, Vector2D cameraPos, float cameraScale, int color, const TCHAR* string);

void RangeRender(Vector2DInt first, Vector2DInt second, Vector2D cameraPos, float cameraScale, int color);
