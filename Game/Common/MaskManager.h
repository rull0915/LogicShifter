#pragma once

/* 使用方法
* 
* MaskManager::
* */

// シングルトン
// マスク管理クラス
class MaskManager
{
	// ----- 変数宣言 ----- //
private:
	int m_maskScreen;

	bool m_isDrawing, isBeingUsed;

private:
	MaskManager()
		: m_maskScreen{ -1 }
	{
		m_maskScreen = MakeScreen(Screen::WIDTH, Screen::HEIGHT, true);

		// マスク機能の初期化を行う
		CreateMaskScreen();
	};
	~MaskManager();

public:
	// インスタンスを返す関数
	static MaskManager& GetInstance()
	{
		static MaskManager instance;

		return instance;
	}

	// マスクスクリーンへの描画を開始する関数
	void StartDrawMask();

	// マスクスクリーンへの描画を終了する関数
	void FinishDrawMask();

	// マスクを適用する関数
	void SetMask(bool reverseFrag);

	// マスクを解除する関数
	void CancelMask();
};

