#pragma once

void DrawQuadrangle(Vector3D p1, Vector3D p2, Vector3D p3, Vector3D p4, int color, bool fillFrag);
void DrawTriangle(Vector2D p1, Vector2D p2, Vector2D p3, int color, bool fillFrag);

void MyDrawBox(Vector2DInt p1, Vector2DInt p2, SquareMatrix3 view, int color, bool fillFrag);
void MyDrawBoxAA(Vector2D p1, Vector2D p2, SquareMatrix3 view, int color, bool fillFrag);

void MyDrawRoundBox(Vector2DInt p1, Vector2DInt p2, int radius , int color, bool fillFrag);
void MyDrawRoundBoxAA(Vector2D p1, Vector2D p2, float radius , int color, bool fillFrag);

// å ÇÃï`âÊ
void MyDrawArc(Vector2DInt centerPos, int radius, float startRad, float endRad, int color);
void MyDrawArcAA(Vector2D centerPos, float radius, float startRad, float endRad, int color);

void MyDrawFormatStringToHandleToCenter(int x, int y, int color, int fontHandle, const TCHAR* string);
void MyDrawExtendFormatStringToHandleToCenter(int x, int y, float rateX, float rateY, int color, int fontHandle, const TCHAR* string);

// êØÇÃï`âÊ
void MyDrawStar(Vector2D centerPos, float outRadius, float inRadius, int color, bool fillFrag);
