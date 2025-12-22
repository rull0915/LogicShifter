#include "GameMath.h"

float NormalizeAngle(float theta)
{
    const double twoPi = 2.0 * DX_PI_F;
    theta = fmod(theta, twoPi); // とりあえず2πで割る
    if (theta < 0) theta += twoPi; // マイナスならお行儀よく前に押し戻す
    return theta;
}

Vector2D GetIntersection(Line line1, Line line2)
{
    // xの分母
    double denominator = (line2.position1.y - line2.position2.y) * (line1.position2.x - line1.position1.x) - (line1.position1.y - line1.position2.y) * (line2.position2.x - line2.position1.x);

    // 分子
    double molecule1 = (line1.position1.x * line1.position2.y - line1.position1.y * line1.position2.x) * (line2.position2.x - line2.position1.x);
    double molecule2 = (line2.position1.x * line2.position2.y - line2.position1.y * line2.position2.x) * (line1.position2.x - line1.position1.x);

    // x 
    double x = (molecule1 - molecule2) / denominator;

    // y
    double y = ((line1.position1.y - line1.position2.y) * (x - line1.position1.x) / (line1.position1.x - line1.position2.x)) + line1.position1.y;
    if ((line1.position1.x - line1.position2.x) == 0)
    {
        y = ((line2.position1.y - line2.position2.y) * (x - line2.position1.x) / (line2.position1.x - line2.position2.x)) + line2.position1.y;
    }

    if (abs(y) < 0.001)
    {
        y = 0;
    }

    return Vector2D{ static_cast<float>(x), static_cast<float>(y) };
}
