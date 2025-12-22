#include "Resources.h"

std::map<std::pair<int, int>, int> m_fontHandles;

// フォントハンドル取得関数
int GetFontHandle(int size, int tick)
{
	std::pair<int, int> pair = std::make_pair(size, tick);

	// 指定したサイズのmapを取得
	auto it = m_fontHandles.find(pair);

	// 指定したサイズのフォントハンドルがあれば
	if (m_fontHandles.find(pair) != m_fontHandles.end())
	{
		// フォントハンドルを返す
		return it->second;
	}

	// 指定したサイズのフォントハンドルがなければ

	// フォントハンドルの作成
	m_fontHandles[pair] = CreateFontToHandle(FONT_NAME, size, tick, DX_FONTTYPE_ANTIALIASING);

	// 返す
	return m_fontHandles[pair];
}

// フォントロード関数
void LoadFonts()
{
}

// フォントハンドル削除関数
void DeleteFontsAll()
{
	for(auto handle : m_fontHandles)
	{
		DeleteFontToHandle(handle.second);
	}
	m_fontHandles.clear();
}

std::unordered_map<std::string, int> m_ghIcons;

int m_ghMouseCursors;

void LoadGraphics()
{
	m_ghIcons["Save"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/SaveIcon.png").c_str());
	m_ghIcons["Load"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/LoadIcon.png").c_str());
	m_ghIcons["Copy"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/CopyIcon.png").c_str());
	m_ghIcons["Paste"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/PasteIcon.png").c_str());
	m_ghIcons["Reset"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/ResetIcon.png").c_str());
	m_ghIcons["Horizontal"] =	LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/HorizontalIcon.png").c_str());
	m_ghIcons["Vertical"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/VerticalIcon.png").c_str());
	m_ghIcons["Range"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/RangeIcon.png").c_str());
	m_ghIcons["Clear"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/ClearIcon.png").c_str());
	m_ghIcons["Stop"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/StopIcon.png").c_str());
	m_ghIcons["PlayOnce"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/PlayOnceIcon.png").c_str());
	m_ghIcons["Play"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/PlayIcon.png").c_str());
	m_ghIcons["PlayFast"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/PlayFastIcon.png").c_str());
	m_ghIcons["Check"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/CheckIcon.png").c_str());
	m_ghIcons["Cancel"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/CancelIcon.png").c_str());
	m_ghIcons["Block"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/BlockIcon.png").c_str());
	m_ghIcons["Undo"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/UndoIcon.png").c_str());
	m_ghIcons["Redo"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/RedoIcon.png").c_str());
	m_ghIcons["Left"] =			LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/LeftIcon.png").c_str());
	m_ghIcons["Right"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/RightIcon.png").c_str());
	m_ghIcons["ArrowLU"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/ArrowLUIcon.png").c_str());
	m_ghIcons["ArrowRU"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/Icons/ArrowRUIcon.png").c_str());

	m_ghIcons["StageMode"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/StageMode.png").c_str());
	m_ghIcons["FreeMode"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/FreeMode.png").c_str());
	m_ghIcons["EditMode"] =		LoadGraph(GetAbsolutePath(L"Resources/Textures/EditMode.png").c_str());

	m_ghMouseCursors = LoadGraph(GetAbsolutePath(L"Resources/Textures/MouseCursors.png").c_str());
}
