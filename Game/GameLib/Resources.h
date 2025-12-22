#pragma once
#include <map>
#include <list>

// ----------- フォント関連 ------------ //

// フォント名
static constexpr const wchar_t* FONT_NAME = L"マキナス 4 flat";

// フォントハンドルのマップ
// サイズ、フォントハンドル
extern std::map<std::pair<int, int>, int> m_fontHandles; 

// フォントハンドルを返す関数
int GetFontHandle(int size, int tick = 1);

// フォントのロード
void LoadFonts();
void DeleteFontsAll();

// ---------- グラフィック関連 ---------- //

// グラフィックハンドル
extern std::unordered_map<std::string, int> m_ghIcons;

extern int m_ghMouseCursors;

// グラフィックのロード
extern void LoadGraphics();

