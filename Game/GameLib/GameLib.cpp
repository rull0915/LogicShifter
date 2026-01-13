#include "GameLib.h"

int m_threadNum = 0;

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

std::wstring GetAbsolutePath(std::wstring relativePath)
{
	// ステージ情報の読み込み
	wchar_t iniFileFolderPath[_MAX_PATH];
	memset(iniFileFolderPath, NULL, _countof(iniFileFolderPath));
	GetModuleFileName(NULL, iniFileFolderPath, _countof(iniFileFolderPath));

	PathRemoveFileSpec(iniFileFolderPath);

	std::wstring path = iniFileFolderPath;
	path += L"\\" + relativePath;

	return path;
}

std::wstring utf8_to_wstring(const std::string& utf8)
{
	if (utf8.empty()) return L"";

	int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
	std::wstring result(size_needed, 0);

	MultiByteToWideChar(CP_UTF8, 0,
		utf8.c_str(), -1,
		&result[0], size_needed
	);

	result.pop_back(); // 終端の\0を削る
	return result;
}

int Gradation(std::vector<int> colors, float ratio)
{
	// サイズが0の場合
	// 0を返す
	if (colors.size() == 0) return 0;

	// サイズが1の場合
	// その色を返す
	if (colors.size() == 1) return colors[0];

	// サイズが2以上の場合
	// 現在がどの位置にいるか調べる
	int currentNum = 0;
	int num = colors.size();

	if (colors.size() == 2) currentNum = 0;
	else 
	{
		for (int i = num - 2; i >= 0; i--)
		{
			// 基準を決める
			float st = (1.0f / (num - 1)) * i;

			// 割合が基準以上なら
			if (ratio >= st) 
			{
				//現在の位置を確定
				currentNum = i;

				break;
			}
		}
	}

	// 色を決める
	auto getR = [](int color) { return color >> 16 & 0xFF; };
	auto getG = [](int color) { return color >> 8 & 0xFF; };
	auto getB = [](int color) { return color >> 0 & 0xFF; };

	float cRatio = (ratio - ((1.0f / (num - 1)) * currentNum)) * (num - 1);

	// 変化前の色
	int bR = getR(colors[currentNum]);
	int bG = getG(colors[currentNum]);
	int bB = getB(colors[currentNum]);

	// 変化後の色
	int aR = getR(colors[currentNum + 1]);
	int aG = getG(colors[currentNum + 1]);
	int aB = getB(colors[currentNum + 1]);

	int r = bR + (aR - bR) * cRatio;
	int g = bG + (aG - bG) * cRatio;
	int b = bB + (aB - bB) * cRatio;

	return GetColor(r, g, b);
}

