#pragma once

void DrawQuadrangle(Vector3D p1, Vector3D p2, Vector3D p3, Vector3D p4, int color, bool fillFrag);

void MyDrawBox(Vector2D p1, Vector2D p2, SquareMatrix3 view, int color, bool fillFrag);

void MyDrawRoundBox(Vector2D p1, Vector2D p2, float radius , int color, bool fillFrag);

void MyDrawFormatStringToHandleToCenter(int x, int y, int color, int fontHandle, const TCHAR* string);
void MyDrawExtendFormatStringToHandleToCenter(int x, int y, float rateX, float rateY, int color, int fontHandle, const TCHAR* string);