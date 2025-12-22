#pragma once
#include "SceneTransition.h"

class IrisTransition : public SceneTransition
{
private:
	int m_irisColor;

	Vector2D m_centerPos;

	// ç≈ëÂÇÃîºåa
	float m_maxRadius;

public:
	IrisTransition(float transTime, Transition::Mode mode, int irisColor = 0x000000, Vector2D centerPos = {Screen::WIDTH / 2, Screen::HEIGHT / 2});

	~IrisTransition();

	void Initialize() override;

	bool Update(float elapsedTime) override;

	void Render() override;
};

