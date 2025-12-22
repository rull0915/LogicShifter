#pragma once

class OnceParticle;

enum class ShapeType
{
	None,
	Circle,
	Block,
};

// パーティクルクラス
class BaseParticle
{
private:
	// パーティクルの形
	ShapeType m_shapeType;

	// 頻度
	float m_frequency;

	// ランダムの幅
	std::pair<Vector2D, Vector2D> m_randomRange;

	// サイズの幅
	std::pair<Vector2D, Vector2D> m_sizeRange;

	// アクティブフラグ
	bool m_isActive;

	// パーティクル群
	std::vector<OnceParticle> m_particles;

public:
	BaseParticle();

	void Initialize(ShapeType type, float freq, std::pair<Vector2D, Vector2D> posRange, std::pair<Vector2D, Vector2D> sizeRange);

	void Update(float elapsedTime);

	void Render(int color);

	void Finalize();
};

class OnceParticle
{
private:
	ShapeType m_type;

	Vector2D m_pos;

	Vector2D m_velocity;

	Vector2D m_size;

	// 寿命
	float m_lifeSpan;

	//経過時間
	float m_sumElap;

	bool m_isDead;

public:
	OnceParticle(ShapeType type, Vector2D pos, Vector2D vel, Vector2D size, float span);
	~OnceParticle();

	void Update(float elapsedTime);

	void Render(int color);

	bool GetIsDead()
	{
		return m_isDead;
	}

private:
	float GetAlpha();
};
