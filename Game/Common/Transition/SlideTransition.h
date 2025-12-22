#pragma once
#include "SceneTransition.h"

class SlideTransition : public SceneTransition
{
	enum class End
	{
		RightUp,
		RightDown,
		LeftUp,
		LeftDown,
	};

private:
	int m_slideColor;

	float m_slideAngle;

	// ç≈èIånÇÃ4ì_ç¿ïW
	std::map<std::string, Vector2D> m_points;

public:
	SlideTransition(float transTime, Transition::Mode mode, int slideColor = 0x000000, float SlideAngle = 0);

	void Initialize() override;

	bool Update(float elapsedTime) override;

	void Render() override;
};
