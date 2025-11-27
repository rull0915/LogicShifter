#pragma once
#include "Vector3D.h"

struct SquareMatrix3
{
	// 行列本体
	float m_matrix[3][3];

	// -------------- 関数宣言 ---------------------------
public:
	// コンストラクタ
	// 単位行列で初期化
	SquareMatrix3();

	// 値を入れる
	SquareMatrix3(float m00, float m01, float m02,
				  float m10, float m11, float m12,
				  float m20, float m21, float m22);

	// 単位行列を返す関数
	static SquareMatrix3 Identity();

	// 平行移動行列を返す関数
	static SquareMatrix3 Translation(float x, float y);

	// 回転行列を返す関数
	static SquareMatrix3 Rotation(float theta);

	// 拡縮行列を返す関数
	static SquareMatrix3 Scale(float x, float y);

	// 逆行列を返す関数
	static SquareMatrix3 Inverse(SquareMatrix3 m);
};

// 演算子オーバーロード
// 行列同士の乗算
SquareMatrix3 operator*(const SquareMatrix3 m1, const SquareMatrix3 m2);

// ベクトルとの乗算
Vector3D operator*(const Vector3D v, const SquareMatrix3 m);
Vector3D operator*(const SquareMatrix3 m, const Vector3D v);

// スカラー倍
SquareMatrix3 operator*(const SquareMatrix3 m, float s);
SquareMatrix3 operator*(float s, const SquareMatrix3 m);
