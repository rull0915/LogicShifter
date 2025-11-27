#pragma once

// 参考: https://easings.net/ja

// イージング関数
namespace Easing
{
	inline float Linear(float x)
	{
		return x;
	}

	inline float EaseInQuad(float x)
	{
		return x * x;
	}

	inline float EaseOutQuad(float x)
	{
		return 1 - (1 - x) * (1 - x);
	}

	inline float EaseInOutQuad(float x)
	{
		return x < 0.5 ? 2 * x * x : 1 - std::pow(-2 * x + 2, 2) / 2;
	}

	inline float EaseOutQuart(float x)
	{
		return (1 - std::pow(1 - x, 4));
	}

}