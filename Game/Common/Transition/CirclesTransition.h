#pragma once
#include "SceneTransition.h"

class CirclesTransition : public SceneTransition
{
private:
	int m_circlesColor;

	int m_circlesNum;

	float m_maxRadius;

public:
	CirclesTransition(float transTime, Transition::Mode mode, int circlesColor = 0x000000, int circlesNum = 8);

	void Initialize() override;

	bool Update(float elapsedTime) override;

	void Render() override;
};

