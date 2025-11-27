#pragma once

class Camera
{
	// 変数宣言 
private:
	Vector2D m_position;

	float m_scale;

	float m_radian;

	// ビュー行列
	SquareMatrix3 m_view;

	// 感度
	float m_sensitivity;

	// 関数宣言
public:
	Camera();

	void Update(Vector2D pos, float rad, float scale);

	// ゲッター
	SquareMatrix3 View() const { return m_view; }
	float GetRad() const { return m_radian; }
};