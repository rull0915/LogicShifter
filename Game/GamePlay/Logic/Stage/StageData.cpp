#include "StageData.h"

StageData::StageData(std::vector<PackedCell>& stage)
	: m_stage{ stage }
	, m_conditions{}
	, m_conditionString{}
	, m_stageSize{ 0, 0 }
	, m_inputNum{ 0 }
	, m_outputNum{ 0 }
	, m_inputInfo{}
	, m_outputInfo{}
{
	m_conditions.resize(std::pow(2, Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_INPUT}]));

	for (int i = 0; i < m_conditions.size(); i++) m_conditions[i].resize(Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_OUTPUT}]);
}

void StageData::Save()
{
	std::wstring fileName = SaveFileDialog();

	json data =
	{
		{"ConditionString" , m_conditionString},
		{"Width" , m_stageSize.x},
		{"Height" , m_stageSize.y},
	};

	for(int i = 0; i < m_inputInfo.size(); i++)
	{
		json input;

		input["PosX"] = m_inputInfo[i].x;
		input["PosY"] = m_inputInfo[i].y;

		data["Inputs"].push_back(input);
	}

	for (int i = 0; i < m_outputInfo.size(); i++)
	{
		json output;

		output["PosX"] = m_outputInfo[i].x;
		output["PosY"] = m_outputInfo[i].y;

		data["Outputs"].push_back(output);
	}

	for(int i = 0; i < std::pow(2, m_inputNum); i++)
	{
		json setting;

		for(int j = 0; j < m_inputNum; j++)
		{
			setting["Input"].push_back((i >> j) & 1);
		}
		for (int j = 0; j < m_outputNum; j++)
		{
			setting["Output"].push_back(m_conditions[i][j]);
		}

		data["Condition"].push_back(setting);
	}

	for (int i = -m_stageSize.y / 2; i < Rounding(m_stageSize.y / 2.0f); i++)
	{
		for (int j = -m_stageSize.x / 2; j < Rounding(m_stageSize.x / 2.0f); j++)
		{
			if (m_stage[GetIndex(j, i)] == 0) continue;

			json cell =
			{
				{"PosX", j},
				{"PosY", i},
				{"Type", GetType(m_stage[GetIndex(j, i)])},
				{"SubType", GetSubType(m_stage[GetIndex(j, i)])},
			};

			data["Stage"].push_back(cell);
		}
	}

	std::ofstream ofs(fileName);

	if(ofs.is_open()) ofs << data.dump(4);

	ofs.close();
}

void StageData::SetCondition(int inputNum, int outputNum, bool condition)
{
	if (inputNum >= m_conditions.size()) return;

	if (outputNum >= m_conditions[inputNum].size()) return;

	m_conditions[inputNum][outputNum] = condition;
}
