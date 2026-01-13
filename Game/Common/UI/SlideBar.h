#pragma once

// スライドバークラス
class SlideBar
{
	// ----- メンバ変数宣言 ----- //
private:

	// バーの幅
	float m_barWidth;

	// バーの中心座標
	Vector2D m_barCenterPos;

	// ボタンの座標
	Vector2D m_buttonCenterPos;

	// ボタンの半径
	float m_buttonRadius;

	// バーの色
	int m_barColor;

	// ボタンの色
	int m_buttonColor;

	// 移動中フラグ
	bool m_isMoving;

	// ----- メンバ関数宣言 ----- //
public:
	// コンストラクタ
	SlideBar(float width, Vector2D pos, float radius = 10, int barColor = 0xCCCCCC, int buttonColor = 0x55CC55);

	// 初期化関数
	void Initialize();

	// 更新関数
	void Update();

	// 描画関数
	void Render();

	// 終了関数
	void Finalize();

	// 値を返す関数
	float GetResult();

	// 値をセットする関数(0 ~ 1)
	void SetResult(float val);
};

