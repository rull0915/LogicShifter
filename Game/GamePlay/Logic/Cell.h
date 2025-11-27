#pragma once

//#include "device_launch_parameters.h"

// Cell構造体 ルール

// 上位2bitでTypeを管理
// 次の2bitでSubTypeを管理
// 末尾4bitで4方向への信号を管理

// 合計1byteのためchar型一つで管理

// Type
// 0: Wire
// 1: Input
// 2: Output
// 3: Others

// SubType
// Wire
// 0: None
// 1: Normal
// 2: Cross
// 3: Light

// Input
// 1: And
// 2: Or
// 3: Xor

// Output
// 1: Normal
// 2: Not

// Others
// 1: Wall
// 2: Button

// Signal
// 上位から0,1,2,3bitとすると、
// 0: up
// 1: right
// 2: down
// 3: left

// 例: 10010010
// Typeは上位2bitが10のため、2のOutput
// SubTypeは次2bitが01のため1のNot
// 各信号は下のみON

// このように扱うこととする。

#define PackedCell unsigned char
#define CellType int
#define CellSubType int

#define CellTypes std::pair<CellType, CellSubType>

// タイプ
#define TYPE_OTHERS 0
#define TYPE_WIRE	1
#define TYPE_INPUT	2
#define TYPE_OUTPUT 3

// サブタイプ
// 導線
#define SUBTYPE_NONE   0
#define SUBTYPE_NORMAL 1
#define SUBTYPE_CROSS  2
#define SUBTYPE_LIGHT  3

// 入力
#define SUBTYPE_AND		1
#define SUBTYPE_OR		2
#define SUBTYPE_BUTTON  3

// 出力
#define SUBTYPE_NORMAL 1
#define SUBTYPE_NOT    2


// 他
#define SUBTYPE_WALL   1
#define SUBTYPE_INPUT  2
#define SUBTYPE_OUTPUT 3

static constexpr unsigned char MASK_TYPE		= 0b11000000;
static constexpr unsigned char MASK_SUBTYPE		= 0b00110000;
static constexpr unsigned char MASK_UP			= 0b00001000;
static constexpr unsigned char MASK_RIGHT		= 0b00000100;
static constexpr unsigned char MASK_DOWN		= 0b00000010;
static constexpr unsigned char MASK_LEFT		= 0b00000001;

// 各信号のゲッター関数
// マスクを使用し各信号を持っているかを取得
inline bool GetUpSignal		(PackedCell c)	{ return (c & MASK_UP)		!= 0; }
inline bool GetRightSignal(PackedCell c) { return (c & MASK_RIGHT) != 0; }
inline bool GetDownSignal(PackedCell c) { return (c & MASK_DOWN) != 0; }
inline bool GetLeftSignal(PackedCell c) { return (c & MASK_LEFT) != 0; }

// 各信号のセッター関数
inline void SetUpSignal(PackedCell& c, bool up) { c = (c & static_cast<unsigned char>(~MASK_UP)) | (up << 3); }
inline void SetRightSignal(PackedCell& c, bool right) { c = (c & static_cast<unsigned char>(~MASK_RIGHT)) | (right << 2); }
inline void SetDownSignal(PackedCell& c, bool down) { c = (c & static_cast<unsigned char>(~MASK_DOWN)) | (down << 1); }
inline void SetLeftSignal(PackedCell& c, bool left) { c = (c & static_cast<unsigned char>(~MASK_LEFT)) | (left << 0); }

// Typeゲッター
inline unsigned int GetType(PackedCell c) { return (static_cast<unsigned char>(c) & MASK_TYPE) >> 6; }
// SubTypeゲッター
inline unsigned int GetSubType(PackedCell c) { return (static_cast<unsigned char>(c) & MASK_SUBTYPE) >> 4; }

// Typeセッター
inline void SetType(PackedCell& c, int type) { c = (c & static_cast<unsigned char>(~MASK_TYPE)) | (type << 6); }
// SubTypeセッター
inline void SetSubType	(PackedCell& c, int subType)	{ c = (c & static_cast<unsigned char>(~MASK_SUBTYPE)) | (subType << 4); }



// ---------- 以下メモ ------------ //

/*
* PackedCell = TTSSURDL (T=Type S=SubType URDL=各方向信号)
* 
* シフト演算子を使い6つ右にずらすことで、
* 000000TTとなるためTypeの取得が可能
* (c & 0b11000000を事前にすることで、Type以外を0で埋める)
* Typeは上位2bitのため、なくても問題ないが、SubTypeは必須になるため、統一するためにつけている
* 
* SubTypeの場合、
* したから4bit目のため、c >> 4 で取得できる
* わけではなく、Typeが０でなかった場合0000TTSSとなり、違った値になる
* そのためマスクを使用し、Sの部分以外は0で埋める
* 
* (c & 0b00110000) >> 4;
* 
* セッターに関して
* Sで考える
* はじめに、S以外の場所を元の値、Sを０で初期化する
* (c & 0b11001111の部分)
* そして、引数のSubtypeとor演算することで、Sの部分のbitにSubTypeを入れる。
*/
