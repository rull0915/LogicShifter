#include "MaskManager.h"

MaskManager::~MaskManager()
{
	DeleteMaskScreen();

	DeleteGraph(m_maskScreen);
}

void MaskManager::StartDrawMask()
{
	if (m_isDrawing) return;

	m_isDrawing = true;

	SetDrawScreen(m_maskScreen);

	ClearDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void MaskManager::FinishDrawMask()
{
	m_isDrawing = false;

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(DX_SCREEN_BACK);
}

void MaskManager::SetMask(bool reverseFrag)
{
	SetMaskScreenGraph(m_maskScreen);

	SetUseMaskScreenFlag(TRUE);

	SetMaskReverseEffectFlag(reverseFrag);
}

void MaskManager::CancelMask()
{
	SetUseMaskScreenFlag(FALSE);
}
