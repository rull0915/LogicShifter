#pragma once

// 2次元ベクトル
struct Vector2D
{
	float x;
	float y;
};

struct Vector2DInt
{
	int x;
	int y;
};

// ------ 演算子のオーバーロード ------ //

// +演算子
inline Vector2D operator+(Vector2D v1, Vector2D v2)
{
	return Vector2D{ v1.x + v2.x, v1.y + v2.y };
}
inline Vector2DInt operator+(Vector2DInt v1, Vector2DInt v2)
{
	return Vector2DInt{ v1.x + v2.x, v1.y + v2.y };
}


// -演算子
inline Vector2D operator-(Vector2D v1, Vector2D v2)
{
	return Vector2D{ v1.x - v2.x, v1.y - v2.y };
}
inline Vector2DInt operator-(Vector2DInt v1, Vector2DInt v2)
{
	return Vector2DInt{ v1.x - v2.x, v1.y - v2.y };
}

// *演算子
inline Vector2D operator*(float a, Vector2D v1)
{
	return Vector2D{ v1.x * a, v1.y * a };
}
inline Vector2D operator*(Vector2D v1, float a)
{
	return a * v1;
}

// /演算子
inline Vector2D operator/(Vector2D v1, float a)
{
	return Vector2D{ v1.x / a, v1.y / a };
}
inline Vector2DInt operator/(Vector2DInt v1, int a)
{
	return Vector2DInt{ v1.x / a, v1.y / a };
}

// ==演算子
inline bool operator==(Vector2D v1, Vector2D v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

// +=演算子
inline Vector2D& operator+=(Vector2D& v1, Vector2D v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

// -=演算子
inline Vector2D& operator-=(Vector2D& v1, Vector2D v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}
inline Vector2DInt& operator-=(Vector2DInt& v1, Vector2DInt v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

// *=演算子
inline Vector2D& operator*=(Vector2D& v1, int a)
{
	v1.x *= a;
	v1.y *= a;
	return v1;
}

// /=演算子
inline Vector2D& operator/=(Vector2D& v1, int a)
{
	v1.x /= a;
	v1.y /= a;
	return v1;
}

inline bool operator==(const Vector2DInt& a, const Vector2DInt& b)
{
	return a.x == b.x && a.y == b.y;
}

// ------ その他関数 ------ //
// 長さ取得関数
// ベクトルの長さ
inline float GetLength(Vector2D v1)
{
	float a = v1.x * v1.x + v1.y * v1.y;

	return sqrt(a);
}
// 2点間の距離
inline float GetLength(Vector2D point1, Vector2D point2)
{
	Vector2D a = point1 - point2;

	return GetLength(a);
}

// 正規化
inline Vector2D& Normalize(Vector2D& v1)
{
	float length = GetLength(v1);

	v1 /= length;
	return v1;
}

// 内積
inline float Dot(Vector2D v1, Vector2D v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// 外積
inline float Cross(Vector2D v1, Vector2D v2)
{
	return v1.x * v2.y + v1.y * v2.x;
}

// int型のVector2Dを返す関数
inline Vector2DInt ToVector2DInt(Vector2D v1)
{
	return Vector2DInt{ static_cast<int>(v1.x), static_cast<int>(v1.y) };
}

// floatのVector2Dを返す関数
inline Vector2D ToVector2DFloat(Vector2DInt v1)
{
	return Vector2D{ static_cast<float>(v1.x), static_cast<float>(v1.y) };
}


namespace std {
	template <>
	struct hash<Vector2DInt> {
		size_t operator()(const Vector2DInt& v) const noexcept {
			// ハッシュ
			return (size_t)((v.x * 73856093) ^ (v.y * 19349663));
		}
	};
}
