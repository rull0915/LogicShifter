#pragma once
#include <cmath>
#include <functional>

// 3次元ベクトル
struct Vector3D
{
	float x;
	float y;
	float z;
};

struct Vector3DInt
{
	int x;
	int y;
	int z;
};

// ------ 演算子のオーバーロード ------ //

// +演算子
inline Vector3D operator+(Vector3D v1, Vector3D v2)
{
	return Vector3D{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
inline Vector3DInt operator+(Vector3DInt v1, Vector3DInt v2)
{
	return Vector3DInt{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// -演算子
inline Vector3D operator-(Vector3D v1, Vector3D v2)
{
	return Vector3D{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
inline Vector3DInt operator-(Vector3DInt v1, Vector3DInt v2)
{
	return Vector3DInt{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// *演算子
inline Vector3D operator*(float a, Vector3D v1)
{
	return Vector3D{ v1.x * a, v1.y * a, v1.z * a };
}
inline Vector3D operator*(Vector3D v1, float a)
{
	return a * v1;
}

// /演算子
inline Vector3D operator/(Vector3D v1, float a)
{
	return Vector3D{ v1.x / a, v1.y / a, v1.z / a };
}
inline Vector3DInt operator/(Vector3DInt v1, int a)
{
	return Vector3DInt{ v1.x / a, v1.y / a, v1.z / a };
}

// ==演算子
inline bool operator==(Vector3D v1, Vector3D v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}
inline bool operator==(const Vector3DInt& a, const Vector3DInt& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

// +=演算子
inline Vector3D& operator+=(Vector3D& v1, Vector3D v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

// -=演算子
inline Vector3D& operator-=(Vector3D& v1, Vector3D v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}
inline Vector3DInt& operator-=(Vector3DInt& v1, Vector3DInt v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

// *=演算子
inline Vector3D& operator*=(Vector3D& v1, float a) // int から float に修正（ベクトルの拡大縮小に対応）
{
	v1.x *= a;
	v1.y *= a;
	v1.z *= a;
	return v1;
}

// /=演算子
inline Vector3D& operator/=(Vector3D& v1, float a) // int から float に修正
{
	v1.x /= a;
	v1.y /= a;
	v1.z /= a;
	return v1;
}


// ------ その他関数 ------ //
// 長さ取得関数
// ベクトルの長さ
inline float GetLength(Vector3D v1)
{
	float a = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
	return sqrt(a);
}
// 2点間の距離
inline float GetLength(Vector3D point1, Vector3D point2)
{
	Vector3D a = point1 - point2;
	return GetLength(a);
}

// 正規化
inline Vector3D& Normalize(Vector3D& v1)
{
	float length = GetLength(v1);
	if (length > 0.0f) // 0除算防止
	{
		v1 /= length;
	}
	return v1;
}

// 内積
inline float Dot(Vector3D v1, Vector3D v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// 外積（3次元では結果もベクトルになります）
inline Vector3D Cross(Vector3D v1, Vector3D v2)
{
	return Vector3D{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

// int型のVector3Dを返す関数
inline Vector3DInt ToVector3DInt(Vector3D v1)
{
	return Vector3DInt{ static_cast<int>(v1.x), static_cast<int>(v1.y), static_cast<int>(v1.z) };
}

// floatのVector3Dを返す関数
inline Vector3D ToVector3DFloat(Vector3DInt v1)
{
	return Vector3D{ static_cast<float>(v1.x), static_cast<float>(v1.y), static_cast<float>(v1.z) };
}


namespace std {
	template <>
	struct hash<Vector3DInt> {
		size_t operator()(const Vector3DInt& v) const noexcept {
			// 3次元用の空間ハッシュ（素数 83492791 を追加）
			return (size_t)((v.x * 73856093) ^ (v.y * 19349663) ^ (v.z * 83492791));
		}
	};
}