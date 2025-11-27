#pragma once

// ----- 列挙型宣言 ----- //
enum class PlayMode
{
	Stage,
	Edit,
	Free,
};

// ----- 構造体宣言 ----- //
struct AABB
{
	Vector2D min;
	Vector2D max;
};

struct AttackAABB
{
	AABB collide;

	bool isActive;
	int damage;
};

//　スクリーン座標への変換関数
Vector3D ToScreen(Vector4D v);

// 中心座標を求める関数
Vector3D GetCenterPos(const std::vector<Vector3D>&);
Vector4D GetCenterPos(const std::vector<Vector4D>&);

// ボックスの衝突判定関数
bool IsCollide(AABB b1, AABB b2);

bool IsCollide(AttackAABB at, AABB a);

inline int HSVToRGB(int h, int s, int v)
{
	// rgbの最大と最小を求める
	int max, min;
	max = v;
	min = max - ((static_cast<float>(s) / 255) * max);

	// それぞれの値を求める
	int r = 0, g = 0, b = 0;

	if (0 <= h && h < 60)
	{
		r = max;
		g = (static_cast<float>(h) / 60) * (max - min) + min;
		b = min;
	}
	else if (h < 120)
	{
		r = ((120 - static_cast<float>(h)) / 60) * (max - min) + min;
		g = max;
		b = min;
	}
	else if (h < 180)
	{
		r = min;
		g = max;
		b = ((static_cast<float>(h) - 120) / 60) * (max - min) + min;
	}
	else if (h < 240)
	{
		r = min;
		g = ((240 - static_cast<float>(h)) / 60) * (max - min) + min;
		b = max;
	}
	else if (h < 300)
	{
		r = ((static_cast<float>(h) - 240) / 60) * (max - min) + min;
		g = min;
		b = max;
	}
	else if (h <= 360)
	{
		r = max;
		g = min;
		b = ((360 - static_cast<float>(h)) / 60) * (max - min) + min;
	}

	return r * 0x010000 + g * 0x0100 + b;
}

inline void RGBToHSV(int rgb, int& h, int& s, int& v)
{
	int r = (rgb >> 16) & 0b11111111;
	int g = (rgb >> 8) & 0b11111111;
	int b = (rgb) & 0b11111111;

	int max = ((r > g ? r : g) > b ? (r > g ? r : g) : b);
	int min = ((r < g ? r : g) < b ? (r < g ? r : g) : b);

	if (r > g && r > b) h = 60 * (static_cast<float>(g - b) / (max - min));
	else if (g > b) h = 60 * (static_cast<float>(b - r) / (max - min)) + 120;
	else if (max != min) h = 60 * (static_cast<float>(r - g) / (max - min)) + 240;
	else h = 0;

	if (h < 0) h += 360;

	if (max == 0) s = 0;
	else s = (static_cast<float>(max - min) / max) * 255;
	v = max;
}

// 弧度法からラジアン
inline float ToRadian(float degrees) 
{
	return (degrees / 180.f) * DX_PI_F;
}

// ラジアンから弧度法
inline float ToDegrees(float radian)
{
	return (radian / DX_PI_F) * 180;
}

inline int Rounding(float num)
{
	int a = static_cast<int>(num);

	if (num < a + 0.5f) return a;
	else return a + 1;
}
