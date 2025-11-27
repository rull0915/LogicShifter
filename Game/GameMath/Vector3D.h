#pragma once

// 3ŸŒ³ƒxƒNƒgƒ‹
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

// ------ ‰‰Zq‚ÌƒI[ƒo[ƒ[ƒh ------ //

// +‰‰Zq
inline Vector3D operator+(Vector3D v1, Vector3D v2)
{
	return Vector3D{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// -‰‰Zq
inline Vector3D operator-(Vector3D v1, Vector3D v2)
{
	return Vector3D{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// *‰‰Zq
inline Vector3D operator*(float a, Vector3D v1)
{
	return Vector3D{ v1.x * a, v1.y * a, v1.z * a };
}
inline Vector3D operator*(Vector3D v1, float a)
{
	return a * v1;
}

// /‰‰Zq
inline Vector3D operator/(Vector3D v1, float a)
{
	return Vector3D{ v1.x / a, v1.y / a, v1.z / a };
}

// ==‰‰Zq
inline bool operator==(Vector3D v1, Vector3D v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

// !=‰‰Zq
inline bool operator!=(Vector3D v1, Vector3D v2)
{
	return !(v1 == v2);
}

// +=‰‰Zq
inline Vector3D& operator+=(Vector3D& v1, Vector3D v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

// -=‰‰Zq
inline Vector3D& operator-=(Vector3D& v1, Vector3D v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

// *=‰‰Zq
inline Vector3D& operator*=(Vector3D& v1, int a)
{
	v1.x *= a;
	v1.y *= a;
	v1.z *= a;
	return v1;
}

// /=‰‰Zq
inline Vector3D& operator/=(Vector3D& v1, int a)
{
	v1.x /= a;
	v1.y /= a;
	v1.z /= a;
	return v1;
}

// “àÏ
inline float Dot(Vector3D p, Vector3D q)
{

	return ( p.x * q.x + p.y * q.y + p.z * q.z );
};

// ŠOÏ
inline Vector3D Cross(Vector3D p, Vector3D q)
{
	return Vector3D{ p.y * q.z - p.z * q.y,p.z * q.x - p.x * q.z,p.x * q.y - p.y * q.x };
};

// ’·‚³
inline float GetLength(Vector3D v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// ³‹K‰»
inline Vector3D Normalize(Vector3D v)
{
	float l = GetLength(v);

	return v / l;
}
