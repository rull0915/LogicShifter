#include "MaskManager.h"

MaskManager::~MaskManager()
{
	DeleteMaskScreen();

	DeleteGraph(m_maskScreen);
}

void MaskManager::StartDrawMask()
{
	// 既に描画中ならスキップ
	if (m_isDrawing) return;

	// 描画中フラグをオンに
	m_isDrawing = true;

	// 描画先スクリーンをマスクスクリーンに
	SetDrawScreen(m_maskScreen);

	// スクリーンをclear
	ClearDrawScreen();

	// α値を最大に指定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void MaskManager::FinishDrawMask()
{
	// 描画中フラグをオフに
	m_isDrawing = false;

	// 描画モードを初期化
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 描画スクリーンを元に戻す
	SetDrawScreen(DX_SCREEN_BACK);
}

void MaskManager::SetMask(bool reverseFrag)
{
	// マスクとして使用するスクリーンを指定
	SetMaskScreenGraph(m_maskScreen);

	// マスク機能をオンにする
	SetUseMaskScreenFlag(TRUE);

	// 切り取る部分を反転するかどうか
	SetMaskReverseEffectFlag(reverseFrag);
}

void MaskManager::CancelMask()
{
	// マスク機能をオフにする
	SetUseMaskScreenFlag(FALSE);
}
