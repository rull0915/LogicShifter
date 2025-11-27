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
	DrawBox(p1.x + radius, p1.y, p2.x - radius, p2.y, color, fillFrag);
	DrawBox(p1.x, p1.y + radius, p2.x, p2.y - radius, color, fillFrag);

	DrawCircle(p1.x + radius, p1.y + radius, radius, color, fillFrag); 
	DrawCircle(p2.x - radius, p1.y + radius, radius, color, fillFrag);
	DrawCircle(p1.x + radius, p2.y - radius, radius, color, fillFrag); 
	DrawCircle(p2.x - radius, p2.y - radius, radius, color, fillFrag);
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
