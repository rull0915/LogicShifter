#pragma once

#include "Vector2D.h"

// ü
struct Line
{
    Vector2D position1;
    Vector2D position2;
};

float NormalizeAngle(float theta);

// Œğ“_‚ğ‹‚ß‚é
Vector2D GetIntersection(Line line1, Line line2);
