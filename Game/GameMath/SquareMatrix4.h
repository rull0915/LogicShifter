#pragma once

// --------------------------- 4*4正方行列 ------------------------------- //

struct SquareMatrix4
{
	// 行列本体
	float m_matrix[4][4];

	// -------------- 関数宣言 ---------------------------
public:
	// コンストラクタ
	// 単位行列で初期化
	SquareMatrix4();

	// 値を入れる
	SquareMatrix4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	// 単位行列を返す関数
	static SquareMatrix4 Identity();

	// 平行移動行列を返す関数
	static SquareMatrix4 Translation(float x, float y, float z);

	// 回転行列を返す関数
	static SquareMatrix4 Rotation(float thetaX, float thetaY, float thetaZ);
	static SquareMatrix4 InverseRotation(float thetaX, float thetaY, float thetaZ);
	static SquareMatrix4 RotationX(float thetaX);
	static SquareMatrix4 RotationY(float thetaY);
	static SquareMatrix4 RotationZ(float thetaZ);

	// 拡縮行列を返す関数
	static SquareMatrix4 Scale(float x, float y, float z);

	// 透視投影行列を返す関数
	static SquareMatrix4 Projection(float ViewAngleY, float farZ, float nearZ, float aspect);
};

SquareMatrix4 operator* (SquareMatrix4 m1, SquareMatrix4 m2);

Vector4D operator* (SquareMatrix4 m, Vector4D v);
Vector4D operator* (Vector4D v, SquareMatrix4 m);

// スカラー倍
SquareMatrix4 operator*(const SquareMatrix4 m, float s);
SquareMatrix4 operator*(float s, const SquareMatrix4 m);