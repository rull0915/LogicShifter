#include "GameLib.h"

Vector3D ToScreen(Vector4D v)
{
	Vector3D a = Vec4ToVec3(v);

	return
	{
		((a.x + 1.0f) / 2) * Screen::WIDTH,
		((a.y + 1.0f) / 2) * Screen::HEIGHT,
		((a.z + 1.0f) / 2)
	};
}

Vector3D GetCenterPos(const std::vector<Vector3D>& v)
{
	float x = 0, y = 0, z = 0;

	for (int i = 0; i < v.size(); i++)
	{
		x += v[i].x;
		y += v[i].y;
		z += v[i].z;
	}

	return{ x / v.size(), y / v.size(), z / v.size() };
};

Vector4D GetCenterPos(const std::vector<Vector4D>& v)
{
	float x = 0, y = 0, z = 0, w = 0;

	for (int i = 0; i < v.size(); i++)
	{
		x += v[i].x;
		y += v[i].y;
		z += v[i].z;
		w += v[i].w;
	}

	return{ x / v.size(), y / v.size(), z / v.size(), w / v.size() };
}

bool IsCollide(AABB a, AABB b)
{
	return ((a.min.x <= b.max.x && a.max.x >= b.min.x) &&
		(a.min.y <= b.max.y && a.max.y >= b.min.y));
}

bool IsCollide(AttackAABB at, AABB a)
{
	return IsCollide(at.collide, a);
}

