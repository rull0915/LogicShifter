#include "SlideTransition.h"
#include "../Game/GameMath/GameMath.h"

SlideTransition::SlideTransition(float transTime, Transition::Mode mode, int slideColor, float SlideAngle)
	: SceneTransition(transTime, mode)
	, m_slideColor{ slideColor }
	, m_slideAngle{ NormalizeAngle(SlideAngle) }
{
}

void SlideTransition::Initialize()
{
	// 角度から始点がどの端か求める
	End end;

	if (m_slideAngle >= 0			&& m_slideAngle < DX_PI_F / 2		) end = End::LeftUp;
	if (m_slideAngle >= DX_PI_F / 2 && m_slideAngle < DX_PI_F			) end = End::RightUp;
	if (m_slideAngle >= DX_PI_F		&& m_slideAngle < DX_PI_F * (3.f/2) ) end = End::RightDown;
	if (m_slideAngle >= DX_PI_F * (3.f / 2) && m_slideAngle < DX_PI_F * 2) end = End::LeftDown;

	// 角度からベクトルを算出
	Vector2D stVec = Vector2D{ cosf(m_slideAngle), sinf(m_slideAngle) } * 100;
	Vector2D vrVec = Vector2D{ -sinf(m_slideAngle), cosf(m_slideAngle) } * 100;

	// 各点の座標
	Vector2D RU = Vector2D{ Screen::WIDTH, 0 };
	Vector2D RD = Vector2D{ Screen::WIDTH, Screen::HEIGHT };
	Vector2D LU = Vector2D{ 0, 0 };
	Vector2D LD = Vector2D{ 0, Screen::HEIGHT };

	// 始点によって分岐
	switch (end)
	{
		// 右上始まりの場合
	case SlideTransition::End::RightUp:

		// 右上からvrVec方向の直線と、右下からstVec方向の直線の交点を求める
		m_points["StartLeft"] = GetIntersection( Line{ RU, RU + vrVec }, Line{ RD, RD + stVec } );

		// 右上からvrVec方向の直線と、左上からstVec方向の直線の交点を求める
		m_points["StartRight"] = GetIntersection( Line{ RU, RU + vrVec }, Line{ LU, LU + stVec } );

		// 左下からvrVec方向の直線と、右下からstVec方向の直線の交点を求める
		m_points["EndLeft"]	= GetIntersection(Line{ LD, LD + vrVec }, Line{ RD, RD + stVec });

		// 左下からvrVec方向の直線と、左上からstVec方向の直線の交点を求める
		m_points["EndRight"] = GetIntersection(Line{ LD, LD + vrVec }, Line{ LU, LU + stVec });

		break;
	case SlideTransition::End::RightDown:

		m_points["StartLeft"] = GetIntersection(Line{ RD, RD + vrVec }, Line{ LD, LD + stVec });
		m_points["StartRight"] = GetIntersection(Line{ RD, RD + vrVec }, Line{ RU, RU + stVec });
		m_points["EndLeft"] = GetIntersection(Line{ LU, LU + vrVec }, Line{ LD, LD + stVec });
		m_points["EndRight"] = GetIntersection(Line{ LU, LU + vrVec }, Line{ RU, RU + stVec });

		break;
	case SlideTransition::End::LeftUp:

		m_points["StartLeft"] = GetIntersection(Line{ LU, LU + vrVec }, Line{ RU, RU + stVec });
		m_points["StartRight"] = GetIntersection(Line{ LU, LU + vrVec }, Line{ LD, LD + stVec });
		m_points["EndLeft"] = GetIntersection(Line{ RD, RD + vrVec }, Line{ RU, RU + stVec });
		m_points["EndRight"] = GetIntersection(Line{ RD, RD + vrVec }, Line{ LD, LD + stVec });

		break;
	case SlideTransition::End::LeftDown:

		m_points["StartLeft"] = GetIntersection(Line{ LD, LD + vrVec }, Line{ LU, LU + stVec });
		m_points["StartRight"] = GetIntersection(Line{ LD, LD + vrVec }, Line{ RD, RD + stVec });
		m_points["EndLeft"] = GetIntersection(Line{ RU, RU + vrVec }, Line{ LU, LU + stVec });
		m_points["EndRight"] = GetIntersection(Line{ RU, RU + vrVec }, Line{ RD, RD + stVec });

		break;
	default:
		break;
	}
}

bool SlideTransition::Update(float elapsedTime)
{
	// 経過時間の加算
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_transSec) m_elapsedTime = m_transSec;

	// 遷移時間を超えたかどうか
	return (m_elapsedTime >= m_transSec);
}

void SlideTransition::Render()
{
	// 4点を決める
	Vector2D endLeft;
	Vector2D endRight;

	switch (m_mode)
	{
	case Transition::Mode::In:
		endLeft = m_points["StartLeft"] + (Vector2D(m_points["EndLeft"] - m_points["StartLeft"])) * Easing::EaseOutQuad(m_elapsedTime / m_transSec);
		endRight = m_points["StartRight"] + (Vector2D(m_points["EndRight"] - m_points["StartRight"])) * Easing::EaseOutQuad(m_elapsedTime / m_transSec);
		break;
	case Transition::Mode::Out:
		endLeft = m_points["StartLeft"] + (Vector2D(m_points["EndLeft"] - m_points["StartLeft"])) * Easing::EaseInQuad(1 - m_elapsedTime / m_transSec);
		endRight = m_points["StartRight"] + (Vector2D(m_points["EndRight"] - m_points["StartRight"])) * Easing::EaseInQuad(1 - m_elapsedTime / m_transSec);
		break;
	default:
		break;
	}

	DrawQuadrangleAA(
		m_points["StartLeft"].x, m_points["StartLeft"].y,
		m_points["StartRight"].x, m_points["StartRight"].y,
		endRight.x, endRight.y,
		endLeft.x, endLeft.y, 
		m_slideColor, true
	);
}
