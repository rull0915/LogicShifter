#pragma once
#include <map>
#include <list>

// ----------- フォント関連 ------------ //

// フォント名
static constexpr const wchar_t* FONT_NAME = L"マキナス 4 flat";

// 最大フォントハンドル数
// フォントサイズの数以上にしないと例外
static const int FONTHADNLE_MAX = 20; 

// フォントサイズ
static constexpr int FONT_SIZE_SMALL  = 32;
static constexpr int FONT_SIZE_MEDIUM = 64;
static constexpr int FONT_SIZE_LARGE  = 128;

// フォントハンドルのマップ
// サイズ、フォントハンドル
extern std::map<int, int> m_fontHandles; 

// フォントハンドルを作成順に管理
extern std::list<int> m_fontOrder;

// フォントハンドルを返す関数
int GetFontHandle(int size);

// フォントのロード
void LoadFonts();
void DeleteFontsAll();

// ---------- グラフィック関連 ---------- //

// グラフィックハンドル
extern int m_ghCharacterTile;

extern std::unordered_map<std::string, int> m_ghIcons;

// グラフィックのロード
extern void LoadGraphics();

