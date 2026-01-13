#include "StarCondition.h"
#include "../Game/GamePlay/Logic/ResultInfo.h"

StarCondition::StarCondition(Vector2D pos)
	: m_pos{ pos }
	, m_selectList{ pos + Vector2D{ 0, SIZE.y / 3 }, Vector2D{ SIZE.x * (7.0f / 16), SIZE.y / 4 }}
	, m_secondCondition{ &m_secondString, pos + Vector2D{-SIZE.x / 8, 0}, Vector2D{SIZE.x * (3.0f /	16), SIZE.y / 4} }
	, m_secondString{ L"" }

	, m_cd_cell{ pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3}, Vector2D{ SIZE.x * (3.0f / 16), SIZE.y / 4}}
	, m_cd_second { &m_cd_st_second, pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3}, Vector2D{ SIZE.x * (3.0f / 16), SIZE.y / 4}}
	, m_cd_count  { &m_cd_st_count,  pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3}, Vector2D{ SIZE.x * (3.0f / 16), SIZE.y / 4}}
	, m_cd_height { &m_cd_st_height, pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3}, Vector2D{ SIZE.x * (3.0f / 16), SIZE.y / 4}}
	, m_cd_width  { &m_cd_st_width,  pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3}, Vector2D{ SIZE.x * (3.0f / 16), SIZE.y / 4}}
{
}

void StarCondition::Initialize()
{
	// リストの初期化
	m_selectList.Initialize();

	// 入力ボックスの初期化
	m_secondCondition.Initialize(true);

	// リストの候補の追加
	for (const auto& str : THIRD_CONDITIONS) m_selectList.AddChoice(str);

	// 
	m_cd_cell.Initialize();
	m_cd_second.Initialize();
	m_cd_count.Initialize();
	m_cd_height.Initialize();
	m_cd_width.Initialize();

	for (const auto& str : CELL_STRINGS) m_cd_cell.AddChoice(str.first);
}

void StarCondition::Update()
{
	if(!m_secondCondition.IsInputting() && !GetThirdIsActive()) m_selectList.Update();

	if(!m_selectList.GetIsOpen()) m_secondCondition.Update();

	// 3つ目の条件で分岐
	const std::wstring& thirdCondition = m_selectList.GetChoiced();

	if(thirdCondition == THIRD_CONDITIONS[0])
	{
		m_cd_cell.Update();
	}
	else if(thirdCondition == THIRD_CONDITIONS[1])
	{
		m_cd_second.Update();
	}
	else if(thirdCondition == THIRD_CONDITIONS[2])
	{
		m_cd_count.Update();
	}
	else if (thirdCondition == THIRD_CONDITIONS[3])
	{
		m_cd_height.Update();
	}
	else if (thirdCondition == THIRD_CONDITIONS[4])
	{
		m_cd_width.Update();
	}

	// 位置の更新
	PosUpdate();
}

void StarCondition::Render()
{
	// 背景の描画
	DrawBox(m_pos.x - SIZE.x / 2, m_pos.y - SIZE.y / 2, m_pos.x + SIZE.x / 2, m_pos.y + SIZE.y / 2, BACK_COLOR, true);

	// 星の描画
	for(int i = 0; i < 3; i++)
	{
		Vector2D pos = { m_pos.x - SIZE.x * (7.0f / 16), m_pos.y + (i - 1) * (SIZE.y / 3) };
		MyDrawStar(pos, SIZE.y / 8, SIZE.y / 24, STAR_COLOR, true);
	}

	// 文字列系の描画
	int posX = static_cast<int>(m_pos.x - SIZE.x * (3.0f / 8));
	DrawStringToHandle(posX, m_pos.y - SIZE.y * (5.0f / 12), L"クリアで獲得", 0xF2F2F2, GetFontHandle(SIZE.y / 6));
	DrawStringToHandle(posX, m_pos.y - SIZE.y * (1.0f / 12), L"実行", 0xF2F2F2, GetFontHandle(SIZE.y / 6));
	DrawStringToHandle(m_pos.x, m_pos.y - SIZE.y * (1.0f / 12), L"回以下で獲得", 0xF2F2F2, GetFontHandle(SIZE.y / 6));
	DrawStringToHandle(posX, m_pos.y + SIZE.y * (3.0f / 12), L"条件:", 0xF2F2F2, GetFontHandle(SIZE.y / 6));

	// 各ブロックの描画
	if (m_secondCondition.IsInputting())
	{
		m_selectList.Render();
		m_secondCondition.Render();
	}
	else
	{
		m_secondCondition.Render();
		m_selectList.Render();
	}

	// 3つ目の条件で分岐
	const std::wstring& thirdCondition = m_selectList.GetChoiced();

	if (thirdCondition == THIRD_CONDITIONS[0])
	{
		m_cd_cell.Render();
	}
	else if (thirdCondition == THIRD_CONDITIONS[1])
	{
		m_cd_second.Render();
	}
	else if (thirdCondition == THIRD_CONDITIONS[2])
	{
		m_cd_count.Render();
	}
	else if (thirdCondition == THIRD_CONDITIONS[3])
	{
		m_cd_height.Render();
	}
	else if (thirdCondition == THIRD_CONDITIONS[4])
	{
		m_cd_width.Render();
	}
}

void StarCondition::Finalize()
{
}

bool StarCondition::GetIsActive()
{
	return {
		m_selectList.GetIsOpen() ||
		m_secondCondition.IsInputting() || 

		GetThirdIsActive()
	};
}

void StarCondition::SaveToJson(json& name)
{
	// jsonに項目を追加
	name["Conditions"];

	// 第二条件
	json second = { {"second", std::stoi(m_secondString)} };

	int id = -1;
	for(int i = 0; i < THIRD_CONDITIONS.size(); i++)
	{
		if(THIRD_CONDITIONS[i] == m_selectList.GetChoiced())
		{
			id = i;
			break;
		}
	}

	// 第三条件
	json third = { 
		{"Condition", m_selectList.GetChoiced()}, 
		{"ConditionId", id}, 
		{"Value", GetThirdValue()}
	};

	name["Conditions"].push_back(second);
	name["Conditions"].push_back(third);
}

bool StarCondition::IsCompleted()
{
	bool con1 = m_secondString != L"";

	const std::wstring& thirdCondition = m_selectList.GetChoiced();
	bool con2 = thirdCondition != L"";

	if (thirdCondition == THIRD_CONDITIONS[0])		con2 = m_cd_cell.GetChoiced() != L"";
	else if (thirdCondition == THIRD_CONDITIONS[1]) con2 = m_cd_st_second != L"";
	else if (thirdCondition == THIRD_CONDITIONS[2]) con2 = m_cd_st_count != L"";
	else if (thirdCondition == THIRD_CONDITIONS[3]) con2 = m_cd_st_height != L"";
	else if (thirdCondition == THIRD_CONDITIONS[4]) con2 = m_cd_st_width != L"";

	return con1 && con2;
}

void StarCondition::PosUpdate()
{
	m_selectList.SetPos(m_pos + Vector2D{ 0, SIZE.y / 3 });

	m_secondCondition.SetPos(m_pos + Vector2D{ -SIZE.x / 8, 0 });

	m_cd_cell.SetPos(m_pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3 });
	
	m_cd_second.SetPos(m_pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3 });

	m_cd_count.SetPos(m_pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3 });

	m_cd_height.SetPos(m_pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3 });

	m_cd_width.SetPos(m_pos + Vector2D{ SIZE.x * (11.0f / 32), SIZE.y / 3 });
}

bool StarCondition::GetThirdIsActive()
{
	return {
		m_cd_cell.GetIsOpen() ||
		m_cd_second.IsInputting() ||
		m_cd_count.IsInputting() || 
		m_cd_height.IsInputting() || 
		m_cd_width.IsInputting() 
	};
}

int StarCondition::GetThirdValue()
{
	const std::wstring& thirdCondition = m_selectList.GetChoiced();

	if (thirdCondition == THIRD_CONDITIONS[0])
	{
		return CELL_STRINGS.at(m_cd_cell.GetChoiced());
	}
	else if (thirdCondition == THIRD_CONDITIONS[1])
	{
		return std::stoi(m_cd_st_second);
	}
	else if (thirdCondition == THIRD_CONDITIONS[2])
	{
		return std::stoi(m_cd_st_count);
	}
	else if (thirdCondition == THIRD_CONDITIONS[3])
	{
		return std::stoi(m_cd_st_height);
	}
	else if (thirdCondition == THIRD_CONDITIONS[4])
	{
		return std::stoi(m_cd_st_width);
	}
}
