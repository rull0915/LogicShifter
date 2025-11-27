#pragma once

// 4次元ベクトル
struct Vector4D
{
	float x;
	float y;
	float z;
	float w;
};
struct Vector4DInt
{
	int x;
	int y;
	int z;
	int w;
};

// ------ 演算子のオーバーロード ------ //

// +演算子
inline Vector4D operator+(Vector4D v1, Vector4D v2)
{
	return Vector4D{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}

// -演算子
inline Vector4D operator-(Vector4D v1, Vector4D v2)
{
	return Vector4D{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}

// *演算子
inline Vector4D operator*(int a, Vector4D v1)
{
	return Vector4D{ v1.x * a, v1.y * a, v1.z * a, v1.w * a };
}
inline Vector4D operator*(Vector4D v1, int a)
{
	return a * v1;
}

// /演算子
inline Vector4D operator/(Vector4D v1, int a)
{
	return Vector4D{ v1.x / a, v1.y / a, v1.z / a, v1.w / a };
}

// +=演算子
inline Vector4D& operator+=(Vector4D& v1, Vector4D v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
	return v1;
}

// -=演算子
inline Vector4D& operator-=(Vector4D& v1, Vector4D v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
	return v1;
}

// *=演算子
inline Vector4D& operator*=(Vector4D& v1, int a)
{
	v1.x *= a;
	v1.y *= a;
	v1.z *= a;
	v1.w *= a;
	return v1;
}

// /=演算子
inline Vector4D& operator/=(Vector4D& v1, int a)
{
	v1.x /= a;
	v1.y /= a;
	v1.z /= a;
	v1.w /= a;
	return v1;
}

// ==演算子
inline bool operator==(Vector4D v1, Vector4D v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w);
}

// !=演算子
inline bool operator!=(Vector4D v1, Vector4D v2)
{
	return !(v1 == v2);
}

// 同次座標変換用
inline Vector3D Vec4ToVec3(Vector4D v)
{
	return
	{
		v.x / -v.w,
		v.y / -v.w,
		v.z / -v.w
	};
}
