#pragma once

namespace COLORS
{
    // ===== äÓñ{êF =====
    constexpr int WHITE = 0xFFFFFF;
    constexpr int BLACK = 0x000000;
    constexpr int RED = 0xFF0000;
    constexpr int GREEN = 0x00FF00;
    constexpr int BLUE = 0x0000FF;

    constexpr int YELLOW = 0xFFFF00;
    constexpr int CYAN = 0x00FFFF;
    constexpr int MAGENTA = 0xFF00FF;

    // ===== ÉOÉåÅ[ÉXÉPÅ[Éã =====
    constexpr int GRAY10 = 0x191919;
    constexpr int GRAY25 = 0x404040;
    constexpr int GRAY50 = 0x808080;
    constexpr int GRAY75 = 0xC0C0C0;
    constexpr int GRAY90 = 0xE6E6E6;

    // ===== ê‘ån =====
    constexpr int DARK_RED = 0x800000;
    constexpr int ORANGE = 0xFFA500;
    constexpr int TOMATO = 0xFF6347;
    constexpr int PINK = 0xFFC0CB;
    constexpr int HOT_PINK = 0xFF69B4;

    // ===== óŒån =====
    constexpr int DARK_GREEN = 0x006400;
    constexpr int LIME = 0x32CD32;
    constexpr int FOREST = 0x228B22;
    constexpr int OLIVE = 0x808000;
    constexpr int MINT = 0xAAF0D1;

    // ===== ê¬ån =====
    constexpr int NAVY = 0x000080;
    constexpr int ROYAL_BLUE = 0x4169E1;
    constexpr int SKY_BLUE = 0x87CEEB;
    constexpr int DEEP_SKY = 0x00BFFF;
    constexpr int STEEL_BLUE = 0x4682B4;

    // ===== éáån =====
    constexpr int PURPLE = 0x800080;
    constexpr int INDIGO = 0x4B0082;
    constexpr int VIOLET = 0xEE82EE;
    constexpr int LAVENDER = 0xE6E6FA;

    // ===== íÉÅEígêFån =====
    constexpr int BROWN = 0xA52A2A;
    constexpr int CHOCOLATE = 0xD2691E;
    constexpr int SAND = 0xF4A460;
    constexpr int BEIGE = 0xF5F5DC;

    // ===== UIå¸ÇØ =====
    constexpr int UI_BG_DARK = 0x1E1E1E;
    constexpr int UI_BG_LIGHT = 0xF0F0F0;
    constexpr int UI_TEXT = 0xE6E6E6;
    constexpr int UI_ACCENT = 0x0078FF;
    constexpr int UI_WARNING = 0xFF5050;
    constexpr int UI_SUCCESS = 0x50C878;
}

namespace GRADATION
{
    // ì¯êF
    static const std::vector<int> RAINBOW_UP = { 0xFF0000,0xFF9600,0xFFF000,0x008700,0x0091ff,0x0064be,0x910082 };
    static const std::vector<int> RAINBOW_DOWN = { 0x910082,0x0064be,0x0091ff,0x008700,0xFFF000,0xFF9600,0xFF0000 };

    // ÉÇÉmÉNÉç
    static const std::vector<int> MONOCHROME_UP = { COLORS::WHITE, COLORS::BLACK };
    static const std::vector<int> MONOCHROME_DOWN = { COLORS::BLACK, COLORS::WHITE };
}
