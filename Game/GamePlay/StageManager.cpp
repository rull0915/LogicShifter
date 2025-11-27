#include "StageManager.h"

StageManager::StageManager()
	: m_circuitEditer{ m_cells, m_cameraPos, m_cameraScale }
	, m_conditions{}
	, m_conditionString{}
	, m_fixedPos{}
	, m_clearChecker{ m_cells, m_nextCells, m_conditions }
	, m_clearCheckButton{ {70, 70}, {60, 60}, true, m_ghIcons["Play"]}
	, m_clearFrag{ false }
{
}

void StageManager::Initialize()
{
	// エディタの初期化
	m_circuitEditer.Initialize(PlayMode::Stage);

	// フラグの初期化
	m_clearFrag = false;

	// 各設定の初期化
	m_conditions.Initialize();
	m_conditionString.clear();

	m_fixedPos.clear();
}

void StageManager::Update(float elapsedTime)
{
	if (MouseEnter() & MOUSE_INPUT_MIDDLE)
	{
		m_cameraPos += { static_cast<float>(GetMouseMoveValue().x), static_cast<float>(GetMouseMoveValue().y) };
	}

	ChangeScale(m_cameraScale - static_cast<float>(MouseWheelRot()) / 5);

	// ボタン上にないか
	bool mouseIsOnButton = m_resetButton.MouseIsOnButton();

	// エディタの更新
	m_circuitEditer.Update(elapsedTime);

	// ボタン上になく、UI上になかったら
	if (!mouseIsOnButton && !m_circuitEditer.PointIsOnUI({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) }))
	{
		// クリア判定中じゃなかったら
		if(!m_clearChecker.GetIsActive())
		if(m_fixedPos.find(GetCellIndex(m_mousePos, m_cameraPos, 1.0f / m_cameraScale)) == m_fixedPos.end()) m_circuitEditer.CellUpdate();
	}

	// ボタンの更新
	m_clearCheckButton.Update();

	// ボタンが押されたときの処理
	if (m_clearCheckButton.GetIsPressed())
	{
		// クリア判定中じゃなかったら
		if(!m_clearChecker.GetIsActive())
		{
			// クリア判定開始
			m_clearChecker.Initialize(m_cells);
		}

		m_clearFrag = false;
	}

	m_resetButton.Update();

	// クリア判定の更新
	if (m_clearChecker.Update(elapsedTime) && !m_clearChecker.GetIsActive())
	{
		m_clearFrag = true;
	};
}

void StageManager::Render()
{
	// 背景描画
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, 0x111111, true);

	float scale = (1.0f / m_cameraScale);

	CellRender();

	// グリッド
	GridRender();

	// 境界線
	BorderRender();

	// エディタの描画
	m_circuitEditer.Render();

	// 背景の描画
	DrawBox(30, 30, 110, 110, 0x444444, true);

	// ボタンの描画
	m_clearCheckButton.Render();

	int width = GetDrawFormatStringWidthToHandle(GetFontHandle(48), m_conditionString.c_str());
	DrawFormatStringToHandle(Screen::WIDTH - width, 0, 0xBBBBBB, GetFontHandle(48), m_conditionString.c_str());

	if (m_clearFrag) DrawFormatStringToHandle(0, 500, 0xFF5555, GetFontHandle(64), L"CLEAR!!!!");

	m_resetButton.Render();
}

void StageManager::Load(std::wstring fileName)
{
	// 受け取るjsonを用意
	json data;

	// 読み取り
	std::ifstream ifs(fileName);

	if (ifs.is_open()) ifs >> data;

	ifs.close();

	// jsonから受け取る

	// 条件文
	m_conditionString.resize(data["ConditionString"].size());
	for(int i = 0; i < data["ConditionString"].size(); i++)
	{
		m_conditionString[i] = data["ConditionString"][i];
	}

	// ステージサイズ
	STAGE_WIDTH = data["Width"];
	STAGE_HEIGHT = data["Height"];

	OFFSET_X = STAGE_WIDTH / 2;
	OFFSET_Y = STAGE_HEIGHT / 2;

	// 入出力位置
	for(int i = 0; i < data["Inputs"].size(); i++)
	{
		Vector2DInt pos;
		pos.x = data["Inputs"][i]["PosX"];
		pos.y = data["Inputs"][i]["PosY"];

		m_conditions.inputPoses.push_back(pos);
	}
	for (int i = 0; i < data["Outputs"].size(); i++)
	{
		Vector2DInt pos;
		pos.x = data["Outputs"][i]["PosX"];
		pos.y = data["Outputs"][i]["PosY"];

		m_conditions.outputPoses.push_back(pos);
	}

	// 条件
	for(int i = 0; i < data["Condition"].size(); i++)
	{
		Condition con;

		// 入力を取得
		for (int j = 0; j < data["Condition"][i]["Input"].size(); j++)
		{
			int a = data["Condition"][i]["Input"][j];
			con.inputs.push_back(a);
		}

		// 出力を取得
		for (int j = 0; j < data["Condition"][i]["Output"].size(); j++)
		{
			con.outputs.push_back(data["Condition"][i]["Output"][j]);
		}

		m_conditions.conditions.push_back(con);
	}

	// サイズ確保
	m_cells.clear();
	m_nextCells.clear();

	m_cells.resize(STAGE_WIDTH * STAGE_HEIGHT + 1);
	m_nextCells.resize(STAGE_WIDTH * STAGE_HEIGHT + 1);
	std::fill(m_cells.begin(), m_cells.end(), 0);
	std::fill(m_nextCells.begin(), m_nextCells.end(), 0);

	// ステージ
	for(int i = 0; i < data["Stage"].size(); i++)
	{
		Vector2DInt pos = {data["Stage"][i]["PosX"], data["Stage"][i]["PosY"], };

		PackedCell cell = 0;
		SetType(cell, data["Stage"][i]["Type"]);
		SetSubType(cell, data["Stage"][i]["SubType"]);

		m_fixedPos.insert(pos);
		m_cells[GetIndex(pos.x, pos.y)] = cell;
	}

	m_circuitEditer.SetCellInfo({ TYPE_OTHERS, SUBTYPE_INPUT }, m_conditions.inputPoses);
	m_circuitEditer.SetCellInfo({ TYPE_OTHERS, SUBTYPE_OUTPUT }, m_conditions.outputPoses);
}
