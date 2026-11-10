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
		return x < 0.5f ? 2.0f * x * x : 1.0f - std::powf(-2.0f * x + 2.0f, 2.0f) / 2;
	}

	inline float EaseOutQuart(float x)
	{
		return (1.0f - std::powf(1 - x, 4));
	}

	inline float EaseInExpo(float x)
	{
		return x == 0 ? 0 : std::powf(2, 10 * x - 10);
	}

	inline float EaseOutExpo(float x)
	{
		return x == 1.0f ? 1.0f : 1.0f - std::powf(2.0f, -10.0f * x);
	}

	inline float EaseOutBounce(float x) {
		const float n1 = 7.5625;
		const float d1 = 2.75;

		if (x < 1 / d1) {
			return n1 * x * x;
		}
		else if (x < 2 / d1) {
			return n1 * (x -= 1.5 / d1) * x + 0.75;
		}
		else if (x < 2.5 / d1) {
			return n1 * (x -= 2.25 / d1) * x + 0.9375;
		}
		else {
			return n1 * (x -= 2.625 / d1) * x + 0.984375;
		}
	}

	inline float EaseInBounce(float x) {
		return 1.0f - EaseOutBounce(1.0f - x);
	}
}