#pragma once

// ğŒ\‘¢‘Ì
struct Condition
{
	std::vector<bool> inputs;
	std::vector<bool> outputs;
};

struct Conditions
{
	std::vector<Vector2DInt> inputPoses;
	std::vector<Vector2DInt> outputPoses;

	std::vector<Condition> conditions;

	void Initialize()
	{
		inputPoses.clear();
		outputPoses.clear();

		conditions.clear();
	}
};