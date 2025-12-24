#include "LogicCircuit.h"

int STAGE_WIDTH = 512;
int STAGE_HEIGHT = 512;

int OFFSET_X = STAGE_WIDTH / 2;
int OFFSET_Y = STAGE_HEIGHT / 2;

LogicCircuit::LogicCircuit()
	: m_freeManager{}
	, m_stageManager{}
	, m_editManager{}
	, m_toResult{ false }
{
	LoadBlockColors();
}

LogicCircuit::~LogicCircuit()
{
	SaveBlockColors();
}

void LogicCircuit::Initialize(PlayMode playMode)
{
	m_nowPlayMode = playMode;

	switch (m_nowPlayMode)
	{
	case PlayMode::Stage:
		m_stageManager.Initialize();
	
		m_stageManager.Load(m_selectedFileName);
		break;
	case PlayMode::Edit:
		m_editManager.Initialize();
		break;
	case PlayMode::Free:
		m_freeManager.Initialize();
		break;
	default:
		break;
	}
}

void LogicCircuit::Update(float elapsedTime)
{
	m_toResult = false;

	OFFSET_X = STAGE_WIDTH / 2;
	OFFSET_Y = STAGE_HEIGHT / 2;

	switch (m_nowPlayMode)
	{
	case PlayMode::Stage:
		m_stageManager.Update(elapsedTime);

		m_toResult = m_stageManager.ToResult();
		break;
	case PlayMode::Edit:
		m_editManager.Update(elapsedTime);
		break;
	case PlayMode::Free:
		m_freeManager.Update(elapsedTime);
		break;
	default:
		break;
	}
}

void LogicCircuit::Render()
{
	switch (m_nowPlayMode)
	{
	case PlayMode::Stage:
		m_stageManager.Render();
		break;
	case PlayMode::Edit:
		m_editManager.Render();
		break;
	case PlayMode::Free:
		m_freeManager.Render();
		break;
	default:
		break;
	}
}

void LogicCircuit::Finalize()
{
	m_stageManager.Finalize();
	m_editManager.Finalize();
	m_freeManager.Finalize();
}

void LogicCircuit::SaveBlockColors()
{
	// ファイルへ書き込み

	// 通常時
	std::ofstream file(GetAbsolutePath(L"Resources/Datas/NornalColors.csv"));

	if (file.is_open())
	{
		for(auto color : Cell::COLORS)
		{
			file << color.first.first << ',' << color.first.second << ',' << color.second << '\n';
		}
	}

	file.close();

	// 信号点灯時
	std::ofstream file2(GetAbsolutePath(L"Resources/Datas/SignalColors.csv"));

	if (file2.is_open())
	{
		for (auto color : Cell::ON_SIGNAL_COLORS)
		{
			file2 << color.first.first << ',' << color.first.second << ',' << color.second << '\n';
		}
	}

	file2.close();
}

void LogicCircuit::LoadBlockColors()
{
	// ファイルの読み込み
	std::string item, line;

	std::pair<CellType, CellSubType> pair;
	int color;

	// 通常時
	std::ifstream ifs(GetAbsolutePath(L"Resources/Datas/NornalColors.csv"));

	if (ifs.is_open())
	{
		while (std::getline(ifs, line))
		{
			std::istringstream iss(line);

			// カンマ区切りで分割する
			std::string item;

			getline(iss, item, ',');
			pair.first = std::stoi(item);

			getline(iss, item, ',');
			pair.second = std::stoi(item);

			// タイプ
			getline(iss, item, ',');
			color = stoi(item);

			Cell::COLORS[pair] = color;
		}
	}

	ifs.close();

	// 信号点灯時
	std::ifstream ifs2(GetAbsolutePath(L"Resources/Datas/SignalColors.csv"));

	if (ifs2.is_open()) 
	{
		while (std::getline(ifs2, line))
		{
			std::istringstream iss(line);

			// カンマ区切りで分割する
			std::string item;

			getline(iss, item, ',');
			pair.first = std::stoi(item);

			getline(iss, item, ',');
			pair.second = std::stoi(item);

			// タイプ
			getline(iss, item, ',');
			color = stoi(item);

			Cell::ON_SIGNAL_COLORS[pair] = color;
		}
	}

	ifs2.close();
}
