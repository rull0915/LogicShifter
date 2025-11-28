#pragma once

// ゲージモード
enum class GaugeMode 
{
	Left,
	Right,
};

// ゲージクラス
class Gauge
{
	// -------- 変数宣言 -------- //
private:
	// 位置
	Vector2D m_position;

	// サイズ
	Vector2D m_size;

	// ゲージを左右どっちから増やすか
	GaugeMode m_mode;

	// 背景色
	int m_backColor;

	// 増えていく色
	int m_barColor;

	// 現在の割合
	float m_ratio;

	// 変化前の割合 変化後の割合
	float m_startRatio, m_endRatio;

	// 変化中かどうか
	bool m_isMoving;

	// イージング用の変数
	float m_easingX;

	// マスクスクリーン
	int m_maskScreen;

	// -------- 関数宣言 -------- //
public:
	Gauge(Vector2D pos, Vector2D size, GaugeMode mode, int backColor, int barColor);

	void Initialize();

	void Update(float elapsedTime);

	void Render();

	void SetRatio(float ratio);

	float GetRatio() const { return m_ratio; }
};

