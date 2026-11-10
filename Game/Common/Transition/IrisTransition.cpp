#include "IrisTransition.h"
#include "../Game/Common/MaskManager.h"

IrisTransition::IrisTransition(float transTime, Transition::Mode mode, int irisColor, Vector2D centerPos)
	: SceneTransition(transTime, mode)
	, m_irisColor{ irisColor }
	, m_centerPos{ centerPos }
{
}

IrisTransition::~IrisTransition()
{
}

void IrisTransition::Initialize()
{
	float l1 = GetLength(m_centerPos - Vector2D{ 0, 0 });
	float l2 = GetLength(m_centerPos - Vector2D{ Screen::WIDTH, 0 });
	float l3 = GetLength(m_centerPos - Vector2D{ 0, Screen::HEIGHT });
	float l4 = GetLength(m_centerPos - Vector2D{ Screen::WIDTH, Screen::HEIGHT });

	m_maxRadius = (l1 > l2 ? l1 : l2) > (l3 > l4 ? l3 : l4) ? (l1 > l2 ? l1 : l2) : (l3 > l4 ? l3 : l4);
}

bool IrisTransition::Update(float elapsedTime)
{
	// Œo‰ßŽžŠÔ‚Ì‰ÁŽZ
	m_elapsedTime += elapsedTime;

	if (m_elapsedTime >= m_transSec) m_elapsedTime = m_transSec;

	// ‘JˆÚŽžŠÔ‚ð’´‚¦‚½‚©‚Ç‚¤‚©
	return (m_elapsedTime >= m_transSec);
}

void IrisTransition::Render()
{
	MaskManager::GetInstance().StartDrawMask();

	float radius = 0;

	switch (m_mode)
	{
	case Transition::Mode::In:

		radius = m_maxRadius - m_maxRadius * (Easing::EaseInQuad(m_elapsedTime / m_transSec));

		break;
	case Transition::Mode::Out:

		radius = m_maxRadius * (Easing::EaseInQuad(m_elapsedTime / m_transSec));

		break;
	default:
		break;
	}

	DrawCircle(
		static_cast<int>(m_centerPos.x), 
		static_cast<int>(m_centerPos.y), 
		static_cast<int>(radius), 
		0x000000, true);

	MaskManager::GetInstance().FinishDrawMask();

	MaskManager::GetInstance().SetMask(false);

	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, m_irisColor, true);

	MaskManager::GetInstance().CancelMask();
}
