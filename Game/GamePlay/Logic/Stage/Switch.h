#pragma once

// スイッチクラス
class Switch
{
	enum class State
	{
		On,
		Off,
		ToOn,
		ToOff
	};

	// 変更する変数
	bool& m_changed;

	// 位置
	Vector2D m_position;

	// サイズ
	Vector2D m_size;

	// 状態
	State m_nowState;

	// イージング用変数
	float m_easingX;

	// ----- 関数宣言 ------ //
public:
	Switch(bool& change, Vector2D pos, Vector2D size);
	
	void Initialize();

	void Update(float elapsedTime);

	void Render();

	Vector2D GetPos() const { return m_position; }
	void SetPos(Vector2D pos) { m_position = pos; }

private:
	bool OnMe(Vector2D pos);
};

