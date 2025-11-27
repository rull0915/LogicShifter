#include "Camera.h"

Camera::Camera()
	: m_position{}
	, m_radian{}
	, m_scale{}
	, m_view{}
{
}

void Camera::Update(Vector2D pos, float rad, float scale)
{
	// 各パラメータの更新
	m_position = pos;
	m_radian = rad;
	m_scale = scale;

	static float x = 0;

	// ビュー行列の作成
	m_view = SquareMatrix3::Translation(Screen::WIDTH / 2, Screen::HEIGHT / 2) * SquareMatrix3::Scale(1 / m_scale, 1 / m_scale) * SquareMatrix3::Rotation(-m_radian) * SquareMatrix3::Translation(-m_position.x, -m_position.y);
}
