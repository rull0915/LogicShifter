#pragma once
#include "SceneTransition.h"

class ClockTransition : public SceneTransition
{
private:
	int m_clockColor;

	float m_maxRadius;

	float m_angle;

	Vector2D m_centerPos;

public:
	ClockTransition(float transTime, Transition::Mode mode, int clockColor = 0x000000, Vector2D centerPos = Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT / 2 });
	~ClockTransition();

	void Initialize() override;

	bool Update(float elapsedTime) override;

	void Render() override;

	void ClockRender();
};
