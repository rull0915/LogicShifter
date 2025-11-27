#include "SquareMatrix3.h"

// コンストラクタ
SquareMatrix3::SquareMatrix3()
{
	*this = Identity();
}

SquareMatrix3::SquareMatrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
	: m_matrix{ m00, m01, m02, 
				m10, m11, m12, 
				m20, m21, m22  }
{
}

// 単位行列
SquareMatrix3 SquareMatrix3::Identity()
{
	return SquareMatrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

// 平行移動行列
SquareMatrix3 SquareMatrix3::Translation(float x, float y)
{
	return SquareMatrix3(1, 0, x, 0, 1, y, 0, 0, 1);
}

// 回転行列
SquareMatrix3 SquareMatrix3::Rotation(float theta)
{
	float c = cosf(theta), s = sinf(theta);

	return SquareMatrix3(c, -s, 0, s, c, 0, 0, 0, 1);
}

// 拡縮行列
SquareMatrix3 SquareMatrix3::Scale(float x, float y)
{
	return SquareMatrix3(x, 0, 0, 0, y, 0, 0, 0, 1);
}

SquareMatrix3 SquareMatrix3::Inverse(SquareMatrix3 m)
{
	SquareMatrix3 result(
		 m.m_matrix[1][1] * m.m_matrix[2][2] - m.m_matrix[1][2] * m.m_matrix[2][1],
		-m.m_matrix[0][1] * m.m_matrix[2][2] + m.m_matrix[0][2] * m.m_matrix[2][1],
		 m.m_matrix[0][1] * m.m_matrix[1][2] - m.m_matrix[0][2] * m.m_matrix[1][1],
		-m.m_matrix[1][0] * m.m_matrix[2][2] + m.m_matrix[1][2] * m.m_matrix[2][0],
		 m.m_matrix[0][0] * m.m_matrix[2][2] - m.m_matrix[0][2] * m.m_matrix[2][0],
		-m.m_matrix[0][0] * m.m_matrix[1][2] + m.m_matrix[0][2] * m.m_matrix[1][0],
		 m.m_matrix[1][0] * m.m_matrix[2][1] - m.m_matrix[1][1] * m.m_matrix[2][0],
		-m.m_matrix[0][0] * m.m_matrix[2][1] + m.m_matrix[0][1] * m.m_matrix[2][0],
		 m.m_matrix[0][0] * m.m_matrix[1][1] - m.m_matrix[0][1] * m.m_matrix[1][0]
	);

	float scalar = ( 1 / (m.m_matrix[0][0] * m.m_matrix[1][1] * m.m_matrix[2][2] + m.m_matrix[0][1] * m.m_matrix[1][2] * m.m_matrix[2][0] + m.m_matrix[0][2] * m.m_matrix[1][0] * m.m_matrix[2][1] - m.m_matrix[0][2] * m.m_matrix[1][1] * m.m_matrix[2][0] - m.m_matrix[0][1] * m.m_matrix[1][0] * m.m_matrix[2][2] - m.m_matrix[0][0] * m.m_matrix[1][2] * m.m_matrix[2][1]) );

	return scalar * result;
}

// 行列同士の乗算
SquareMatrix3 operator*(const SquareMatrix3 m1, const SquareMatrix3 m2)
{
	// 返す行列を作成
	SquareMatrix3 result;

	// 9この要素分ループ
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 初期化
			result.m_matrix[i][j] = 0;

			// 要素の計算
			for (int k = 0; k < 3; k++)
			{
				result.m_matrix[i][j] += m1.m_matrix[i][k] * m2.m_matrix[k][j];
			}
		}
	}

	return result;
}

// ベクトルとの乗算
Vector3D operator*(const Vector3D v, const SquareMatrix3 m)
{
	Vector3D r;
	r.x = m.m_matrix[0][0] * v.x + m.m_matrix[0][1] * v.y + m.m_matrix[0][2] * v.z;
	r.y = m.m_matrix[1][0] * v.x + m.m_matrix[1][1] * v.y + m.m_matrix[1][2] * v.z;
	r.z = m.m_matrix[2][0] * v.x + m.m_matrix[2][1] * v.y + m.m_matrix[2][2] * v.z;
	return r;
}

Vector3D operator*(const SquareMatrix3 m, const Vector3D v)
{
	return v * m;
}

SquareMatrix3 operator*(const SquareMatrix3 m, float s)
{
	return SquareMatrix3(
		m.m_matrix[0][0] * s, m.m_matrix[0][1] * s, m.m_matrix[0][2] * s,
		m.m_matrix[1][0] * s, m.m_matrix[1][1] * s, m.m_matrix[1][2] * s,
		m.m_matrix[2][0] * s, m.m_matrix[2][1] * s, m.m_matrix[2][2] * s);
}

SquareMatrix3 operator*(float s, const SquareMatrix3 m)
{
	return m * s;
}