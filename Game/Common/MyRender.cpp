#include "MyRender.h"

void DrawQuadrangle(Vector3D p1, Vector3D p2, Vector3D p3, Vector3D p4, int color, bool fillFrag)
{
	DrawQuadrangleAA(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, color, fillFrag);
}

void MyDrawBox(Vector2D p1, Vector2D p2, SquareMatrix3 view, int color, bool fillFrag)
{ 
	Vector3D p[4] = { {p1.x, p1.y, 1}, {p1.x, p2.y, 1}, {p2.x, p2.y, 1}, {p2.x, p1.y, 1} };

	Vector3D sPos[4] = { p[0] * view, p[1] * view, p[2] * view, p[3] * view };

	DrawQuadrangle(sPos[0], sPos[1], sPos[2], sPos[3], color, fillFrag);
}

void MyDrawRoundBox(Vector2D p1, Vector2D p2, float radius, int color, bool fillFrag)
{
	if (fillFrag)
	{
		DrawBoxAA(p1.x + radius, p1.y, p2.x - radius + 1, p2.y + 1, color, fillFrag);
		DrawBoxAA(p1.x, p1.y + radius, p2.x + 1, p2.y - radius + 1, color, fillFrag);

		DrawCircleAA(p1.x + radius, p1.y + radius, radius, 32, color, fillFrag);
		DrawCircleAA(p2.x - radius, p1.y + radius, radius, 32, color, fillFrag);
		DrawCircleAA(p1.x + radius, p2.y - radius, radius, 32, color, fillFrag);
		DrawCircleAA(p2.x - radius, p2.y - radius, radius, 32, color, fillFrag);
	}
	else 
	{
		DrawLine(p1.x + radius, p1.y, p2.x - radius, p1.y, color, fillFrag);
		DrawLine(p2.x, p1.y + radius, p2.x, p2.y - radius, color, fillFrag);
		DrawLine(p1.x + radius, p2.y, p2.x - radius, p2.y, color, fillFrag);
		DrawLine(p1.x, p1.y + radius, p1.x, p2.y - radius, color, fillFrag);

		MyDrawArc({ p1.x + radius, p1.y + radius }, radius, DX_PI_F, DX_PI_F * (3.f / 2), color);
		MyDrawArc({ p2.x - radius, p1.y + radius},	radius, DX_PI_F * (3.f / 2), DX_PI_F * 2, color);
		MyDrawArc({ p1.x + radius, p2.y - radius }, radius, DX_PI_F * (1.f / 2), DX_PI_F, color);
		MyDrawArc({ p2.x - radius, p2.y - radius }, radius, 0, DX_PI_F * (1.f / 2), color);
	}
}

void MyDrawArc(Vector2D centerPos, float radius, float startRad, float endRad, int color)
{
	const float step = 1.0f / (radius * 2); 

	for (float a = startRad; a <= endRad; a += step) {
		float x = centerPos.x + cosf(a) * radius;
		float y = centerPos.y + sinf(a) * radius;
		DrawPixel(static_cast<int>(x), static_cast<int>(y), color);
	}
}

void MyDrawFormatStringToHandleToCenter(int x, int y, int color, int fontHandle, const TCHAR* string)
{
	int width, height, lineCount;
	GetDrawFormatStringSizeToHandle(&width, &height, &lineCount, fontHandle, string);

	DrawFormatStringToHandle(x - width / 2, y - height / 2, color, fontHandle, string);
}

void MyDrawExtendFormatStringToHandleToCenter(int x, int y, float rateX, float rateY, int color, int fontHandle, const TCHAR* string)
{
	int width, height, lineCount;
	GetDrawExtendFormatStringSizeToHandle(&width, &height, &lineCount, rateX, rateY, fontHandle, string);

	DrawExtendFormatStringToHandle(x - width / 2, y - height / 2, rateX, rateY, color, fontHandle, string);
}
