#include "Resources.h"

std::map<int, int> m_fontHandles;
std::list<int> m_fontOrder;

// フォントハンドル取得関数
int GetFontHandle(int size)
{
	// 指定したサイズのmapを取得
	auto it = m_fontHandles.find(size);

	// 指定したサイズのフォントハンドルがあれば
	if (m_fontHandles.find(size) != m_fontHandles.end())
	{
		// 使用順を最新に更新
		m_fontOrder.remove(size);
		m_fontOrder.push_front(size);

		// フォントハンドルを返す
		return it->second;
	}

	// 指定したサイズのフォントハンドルがなければ

	// フォントハンドルの数が最大値を超えたら
	if(m_fontHandles.size() >= FONTHADNLE_MAX)
	{
		// 古いフォントサイズを取得
		int oldestSize = m_fontOrder.back();

		// 削除
		m_fontOrder.pop_back();

		// フォントハンドルの削除
		DeleteFontToHandle(m_fontHandles[oldestSize]);
		m_fontHandles.erase(oldestSize);
	}

	// フォントハンドルの作成
	m_fontHandles[size] = CreateFontToHandle(FONT_NAME, size, 0, DX_FONTTYPE_ANTIALIASING);

	// 最新を更新
	m_fontOrder.push_front(size);

	// 返す
	return m_fontHandles[size];
}

// フォントロード関数
void LoadFonts()
{
	// よく使うサイズを指定
	const int sizes[] = { FONT_SIZE_SMALL, FONT_SIZE_MEDIUM, FONT_SIZE_LARGE };
	for (int size : sizes) 
	{
		// ハンドルを作成
		int handle = CreateFontToHandle(FONT_NAME, size, 0, DX_FONTTYPE_ANTIALIASING);
		if (handle != -1) 
		{
			// マップに追加
			m_fontHandles[size] = handle;
		}
	}
}

// フォントハンドル削除関数
void DeleteFontsAll()
{
	for(auto handle : m_fontHandles)
	{
		DeleteFontToHandle(handle.second);
	}
	m_fontHandles.clear();
	m_fontOrder.clear();
}

int m_ghCharacterTile = -1;

std::unordered_map<std::string, int> m_ghIcons;

void LoadGraphics()
{
	m_ghCharacterTile =			LoadGraph(L"Resources/Textures/tilemap-characters_packed.png");

	m_ghIcons["Save"] =			LoadGraph(L"Resources/Textures/Icons/SaveIcon.png");
	m_ghIcons["Load"] =			LoadGraph(L"Resources/Textures/Icons/LoadIcon.png");
	m_ghIcons["Copy"] =			LoadGraph(L"Resources/Textures/Icons/CopyIcon.png");
	m_ghIcons["Paste"] =		LoadGraph(L"Resources/Textures/Icons/PasteIcon.png");
	m_ghIcons["Reset"] =		LoadGraph(L"Resources/Textures/Icons/ResetIcon.png");
	m_ghIcons["Horizontal"] =	LoadGraph(L"Resources/Textures/Icons/HorizontalIcon.png");
	m_ghIcons["Vertical"] =		LoadGraph(L"Resources/Textures/Icons/VerticalIcon.png");
	m_ghIcons["Range"] =		LoadGraph(L"Resources/Textures/Icons/RangeIcon.png");
	m_ghIcons["Clear"] =		LoadGraph(L"Resources/Textures/Icons/ClearIcon.png");
	m_ghIcons["Stop"] =			LoadGraph(L"Resources/Textures/Icons/StopIcon.png");
	m_ghIcons["PlayOnce"] =		LoadGraph(L"Resources/Textures/Icons/PlayOnceIcon.png");
	m_ghIcons["Play"] =			LoadGraph(L"Resources/Textures/Icons/PlayIcon.png");
	m_ghIcons["PlayFast"] =		LoadGraph(L"Resources/Textures/Icons/PlayFastIcon.png");
	m_ghIcons["Check"] =		LoadGraph(L"Resources/Textures/Icons/CheckIcon.png");
	m_ghIcons["Cancel"] =		LoadGraph(L"Resources/Textures/Icons/CancelIcon.png");
	m_ghIcons["Block"] =		LoadGraph(L"Resources/Textures/Icons/BlockIcon.png");
	m_ghIcons["Undo"] =			LoadGraph(L"Resources/Textures/Icons/UndoIcon.png");
	m_ghIcons["Redo"] =			LoadGraph(L"Resources/Textures/Icons/RedoIcon.png");
}
