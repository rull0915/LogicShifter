#include "BaseParticle.h"

#pragma region BaseParticle

BaseParticle::BaseParticle()
	: m_shapeType{ ShapeType::None }
	, m_frequency{ 0 }
	, m_randomRange{ std::make_pair<Vector2D, Vector2D>({0, 0}, {0, 0}) }
	, m_sizeRange{ std::make_pair<Vector2D, Vector2D>({0, 0}, {0, 0}) }
	, m_isActive{ false }
	, m_span{ 0 }
{
}

void BaseParticle::Initialize(ShapeType type, float freq, std::pair<Vector2D, Vector2D> randomRange, std::pair<Vector2D, Vector2D> sizeRange, float span)
{
	m_shapeType = type;
	m_frequency = freq;
	m_randomRange = randomRange;
	m_sizeRange = sizeRange;
	m_span = span;

	m_isActive = true;
}

void BaseParticle::Update(float elapsedTime, std::pair<int, int>velRange)
{
	static float sum = 0;
	sum += elapsedTime;

	if(sum >= m_frequency)
	{
		Vector2D pos = {
			min(m_randomRange.first.x, m_randomRange.second.x) + GetRand(static_cast<int>(abs(m_randomRange.second.x - m_randomRange.first.x))),
			min(m_randomRange.first.y, m_randomRange.second.y) + GetRand(static_cast<int>(abs(m_randomRange.second.y - m_randomRange.first.y)))
		};

		Vector2D vel =
		{
			0.0f, static_cast<float>(- velRange.first - GetRand((velRange.second - velRange.first)))
		};

		Vector2D size =
		{
			min(m_sizeRange.first.x, m_sizeRange.second.x) + GetRand(static_cast<int>(abs(m_sizeRange.second.x - m_sizeRange.first.x))),
			min(m_sizeRange.first.y, m_sizeRange.second.y) + GetRand(static_cast<int>(abs(m_sizeRange.second.y - m_sizeRange.first.y)))
		}; 

		// パーティクルの生成
		m_particles.push_back(OnceParticle(m_shapeType, pos, vel, size, m_span));

		// リセット
		sum = 0;
	}

	// パーティクルの更新
	for (auto& par : m_particles) par.Update(elapsedTime);

	// パーティクルの生死チェック
	for (int i = 0; i < m_particles.size(); i++)
	{
		// 死んだパーティクルなら
		if(m_particles[i].GetIsDead())
		{
			// 削除
			m_particles.erase(m_particles.begin() + i);
		}
	}
}

void BaseParticle::Render(int color)
{
	for (auto& par : m_particles) par.Render(color);
}

void BaseParticle::Finalize()
{
}

#pragma endregion

#pragma region OnceParticle

OnceParticle::OnceParticle(ShapeType type, Vector2D pos, Vector2D vel, Vector2D size, float span)
	: m_type{ type }
	, m_pos{ pos }
	, m_velocity{ vel }
	, m_size{ size }
	, m_lifeSpan{ span }
	, m_isDead{ false }
	, m_sumElap{ 0 }
{
}

OnceParticle::~OnceParticle()
{
}

void OnceParticle::Update(float elapsedTime)
{
	// 経過時間の加算
	m_sumElap += elapsedTime;

	if (m_sumElap >= m_lifeSpan) m_isDead = true;

	m_pos += m_velocity * elapsedTime;
}

void OnceParticle::Render(int color)
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(GetAlpha() * 255));

	switch (m_type)
	{
	case ShapeType::Circle:
		DrawCircleAA(m_pos.x, m_pos.y, m_size.x, 32, color, true);
		break;
	case ShapeType::Block:
		DrawBoxAA(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, color, true);
		break;
	default:
		break;
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

float OnceParticle::GetAlpha()
{
	// 割合
	float ratio = m_sumElap / m_lifeSpan;

	if(ratio < 1.0f / 3)
	{
		return Easing::Linear(ratio * 3);
	}
	else if(ratio < 2.0f / 3)
	{
		return 1.0f;
	}
	else
	{
		return Easing::Linear((1.0f - ratio) * 3);
	}
}

#pragma endregion
