#pragma once
#include "Cell.h"

// セルサイズ
static constexpr int BLOCK_SIZE = 64;

// ステージのサイズ
extern int STAGE_WIDTH;
extern int STAGE_HEIGHT;

extern int OFFSET_X;
extern int OFFSET_Y;

namespace Cell
{
	// セルの一覧
	static std::vector<std::pair<CellType, CellSubType>> ALL_CELL
	{
		{TYPE_WIRE,   SUBTYPE_NORMAL},
		{TYPE_WIRE,   SUBTYPE_CROSS},
		{TYPE_WIRE,   SUBTYPE_LIGHT},
		{TYPE_INPUT,  SUBTYPE_BUTTON},
		{TYPE_INPUT,  SUBTYPE_AND},
		{TYPE_INPUT,  SUBTYPE_OR},
		{TYPE_OUTPUT, SUBTYPE_NORMAL},
		{TYPE_OUTPUT, SUBTYPE_NOT},
		{TYPE_OTHERS, SUBTYPE_WALL},
		{TYPE_OTHERS, SUBTYPE_INPUT},
		{TYPE_OTHERS, SUBTYPE_OUTPUT}
	};

	// 各セルの最大数
	static std::map<std::pair<CellType, CellSubType>, int> CELL_MAX_COUNT
	{
		{{TYPE_WIRE,   SUBTYPE_NORMAL},		INT_MAX},
		{ { TYPE_WIRE,   SUBTYPE_CROSS },	INT_MAX },
		{{TYPE_WIRE,   SUBTYPE_LIGHT},		INT_MAX},
		{{TYPE_INPUT,  SUBTYPE_BUTTON},		INT_MAX},
		{{TYPE_INPUT,  SUBTYPE_AND},		INT_MAX},
		{{TYPE_INPUT,  SUBTYPE_OR},			INT_MAX},
		{{TYPE_OUTPUT, SUBTYPE_NORMAL},		INT_MAX},
		{{TYPE_OUTPUT, SUBTYPE_NOT},		INT_MAX},
		{{TYPE_OTHERS, SUBTYPE_WALL},		INT_MAX},
		{{TYPE_OTHERS, SUBTYPE_INPUT},		5},
		{{TYPE_OTHERS, SUBTYPE_OUTPUT},		7}
	};

	// 情報を保持したいセルのタイプ
	static std::vector<CellTypes> GET_INFO_TYPES
	{
		//{TYPE_WIRE,   SUBTYPE_NORMAL},
		//{TYPE_WIRE,   SUBTYPE_CROSS},
		//{TYPE_WIRE,   SUBTYPE_LIGHT},
		//{TYPE_INPUT,  SUBTYPE_BUTTON},
		//{TYPE_INPUT,  SUBTYPE_AND},
		//{TYPE_INPUT,  SUBTYPE_OR},
		//{TYPE_OUTPUT, SUBTYPE_NORMAL},
		//{TYPE_OUTPUT, SUBTYPE_NOT},
		//{TYPE_OTHERS, SUBTYPE_WALL},
		{TYPE_OTHERS, SUBTYPE_INPUT},
		{TYPE_OTHERS, SUBTYPE_OUTPUT}
	};

	// モード毎のボタンの種類
	static std::map<PlayMode, std::vector<std::pair<CellType, CellSubType>>> BUTTONS
	{
		{	
			PlayMode::Free,
			{
				{TYPE_WIRE,   SUBTYPE_NORMAL},
				{TYPE_WIRE,   SUBTYPE_CROSS},
				{TYPE_WIRE,   SUBTYPE_LIGHT},
				{TYPE_INPUT,  SUBTYPE_AND},
				{TYPE_INPUT,  SUBTYPE_OR},
				{TYPE_INPUT,  SUBTYPE_BUTTON},
				{TYPE_OUTPUT, SUBTYPE_NORMAL},
				{TYPE_OUTPUT, SUBTYPE_NOT}
			}
		},
		{
			PlayMode::Edit,
			{
				{TYPE_WIRE,   SUBTYPE_NORMAL},
				{TYPE_WIRE,   SUBTYPE_CROSS},
				{TYPE_WIRE,   SUBTYPE_LIGHT},
				{TYPE_OTHERS, SUBTYPE_WALL},
				{TYPE_INPUT,  SUBTYPE_AND},
				{TYPE_INPUT,  SUBTYPE_OR},
				{TYPE_OUTPUT, SUBTYPE_NORMAL},
				{TYPE_OUTPUT, SUBTYPE_NOT},
				{TYPE_OTHERS, SUBTYPE_INPUT},
				{TYPE_OTHERS, SUBTYPE_OUTPUT},
			}
		},
		{
			PlayMode::Stage,
			{
				{TYPE_WIRE,   SUBTYPE_NORMAL},
				{TYPE_WIRE,   SUBTYPE_CROSS},
				{TYPE_INPUT,  SUBTYPE_AND},
				{TYPE_INPUT,  SUBTYPE_OR},
				{TYPE_OUTPUT, SUBTYPE_NORMAL},
				{TYPE_OUTPUT, SUBTYPE_NOT},
			}
		}
	};

	// 色
	extern std::map<std::pair<CellType, CellSubType>, int> COLORS;

	extern std::map<std::pair<CellType, CellSubType>, int> ON_SIGNAL_COLORS;
}

inline Vector2DInt GetCellIndex(Vector2DInt screenPos, Vector2D cameraPos, float scale)
{
	// ズーム中心補正
	float offsetX = Screen::WIDTH / 2 + Screen::WIDTH / 2 * scale;
	float offsetY = Screen::HEIGHT / 2 + Screen::HEIGHT / 2 * scale;

	float x = (screenPos.x + cameraPos.x - offsetX) / (BLOCK_SIZE * scale);
	float y = (screenPos.y + cameraPos.y - offsetY) / (BLOCK_SIZE * scale);

	if (x <= 0)
	{
		if (x == 0) (screenPos.x + cameraPos.x - offsetX) / (BLOCK_SIZE * scale) < 0 ? x-- : x;
		else x--;
	}
	if (y <= 0)
	{
		if (y == 0) (screenPos.y + cameraPos.y - offsetY) / (BLOCK_SIZE * scale) < 0 ? y-- : y;
		else y--;
	}

	return Vector2DInt{ static_cast<int>(x), static_cast<int>(y) };
}

inline int GetIndex(int x, int y)
{
	return (y + OFFSET_Y) * STAGE_WIDTH + (x + OFFSET_X);
}
