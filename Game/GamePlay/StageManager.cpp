#include "StageManager.h"

StageManager::StageManager()
	: m_circuitEditer{ m_cells, m_cameraPos, m_cameraScale }
	, m_conditions{}
	, m_conditionString{}
	, m_fixedPos{}
	, m_clearChecker{ m_cells, m_nextCells, m_conditions }
	, m_clearCheckButton{ {70, 70}, {60, 60}, true, m_ghIcons["Play"]}
	, m_clearFrag{ false }
	, m_conditionChecker{}
	, m_sumElapsedTime{ 0 }
	, m_executeNum{ 0 }
	, m_toResult{ false }
	, m_pTutorial{}
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

	m_conditionChecker = nullptr;

	m_sumElapsedTime = 0;
	m_executeNum = 0;

	m_toResult = false;

	m_cameraPos = { Screen::WIDTH / 2, Screen::HEIGHT / 2 };
	m_cameraScale = 1.0f;
}

void StageManager::Update(float elapsedTime)
{
	// 経過時間の加算
	m_sumElapsedTime += elapsedTime;

	if (m_pTutorial) m_pTutorial->Update();

	bool tutorialIsActive = !m_pTutorial || (m_pTutorial && m_pTutorial->GetIsActive());

	if (!tutorialIsActive && MouseEnter() & MOUSE_INPUT_MIDDLE)
	{
		m_cameraPos += { static_cast<float>(GetMouseMoveValue().x), static_cast<float>(GetMouseMoveValue().y) };

		m_mouseDrawMode = MouseMode::Move;
	}

	if (!tutorialIsActive) ChangeScale(m_cameraScale - static_cast<float>(MouseWheelRot()) / 5);

	// エディタの更新
	m_circuitEditer.Update(elapsedTime);

	// ボタン上になく、UI上になかったら
	if (!m_circuitEditer.PointIsOnUI({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) }))
	{
		// クリア判定中じゃなかったら
		if (!m_clearChecker.GetIsActive()) 
		{
			if (m_fixedPos.find(GetCellIndex(m_mousePos, m_cameraPos, 1.0f / m_cameraScale)) == m_fixedPos.end()) m_circuitEditer.CellUpdate();
		}
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

			// 実行回数の加算
			m_executeNum++;
		}

		m_clearFrag = false;
	}

	// クリア判定の更新
	if (m_clearChecker.Update(elapsedTime) && !m_clearChecker.GetIsActive())
	{
		if (!m_clearFrag) CheckConditions();

		m_clearFrag = true;

		m_toResult = true;
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

	m_clearChecker.Render();

	if (m_clearChecker.GetIsActive()) DrawFormatStringToHandle(120, 50, 0xFFFFFF, GetFontHandle(32), L"実行中...");
	if (m_clearFrag) DrawFormatStringToHandle(120, 50, 0xFFFFFF, GetFontHandle(32), L"Success!");

	if (m_pTutorial) m_pTutorial->Render();
}

void StageManager::Finalize()
{
	m_clearCheckButton.Finalize();

	m_circuitEditer.Finalize();
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

	// リザルト関連

	// 第二条件の値を取得
	int secondValue = data["Conditions"][0]["second"];

	// 第三条件の値を取得
	int thirdValue = data["Conditions"][1]["Value"];

	// 第三条件の条件文を取得
	std::wstring thirdConditionString;
	thirdConditionString.resize(data["Conditions"][1]["Condition"].size());
	for (int i = 0; i < data["Conditions"][1]["Condition"].size(); i++)
	{
		thirdConditionString[i] = data["Conditions"][1]["Condition"][i];
	}

	// 条件のidを取得
	m_conditionID = data["Conditions"][1]["ConditionId"];

	// リザルト構造体に保存
	ResultInfo::GetInstance().SetStageName(m_conditionString);
	ResultInfo::GetInstance().SetConditions(m_conditions.conditions);

	ResultInfo::GetInstance().SetSecondConditionValue(secondValue);
	ResultInfo::GetInstance().SetThirdConditionValue(thirdValue);
	ResultInfo::GetInstance().SetThirdCondition(thirdConditionString);

	// チュートリアル
	int tutorialID = data["Tutorial"];
	m_pTutorial = std::make_unique<Tutorial>();
	if (m_pTutorial) m_pTutorial->Initialize(static_cast<TutorialType>(tutorialID));
}

void StageManager::CheckConditions()
{
	// 第二条件のチェック
	bool second = m_executeNum <= ResultInfo::GetInstance().GetSecondConditionValue();

	// 第三引数のチェック
	int value = ResultInfo::GetInstance().GetThirdConditionValue();

	switch (m_conditionID)
	{
		// ID 0: NotUsed
	case 0:
		m_conditionChecker = std::make_unique<NotUsedChecker>(value, m_cells, m_fixedPos);
		break;
		// ID 1: TimeChecker
	case 1:
		m_conditionChecker = std::make_unique<TimeChecker>(value, m_sumElapsedTime);
		break;
		// ID 2: CountChecker
	case 2:
		m_conditionChecker = std::make_unique<CountChecker>(value, m_cells, m_fixedPos);
		break;
		// ID 3: HeightChecker
	case 3:
		m_conditionChecker = std::make_unique<HeightChecker>(value, m_cells, m_fixedPos);
		break;
		// ID 4: WidthChecker
	case 4:
		m_conditionChecker = std::make_unique<WidthChecker>(value, m_cells, m_fixedPos);
		break;
	default:
		break;
	}

	bool third = (m_conditionChecker ? m_conditionChecker->IsSatisfied() : false);

	// リザルト構造体にセット
	ResultInfo::GetInstance().SetIsSatisfied(0, true);
	ResultInfo::GetInstance().SetIsSatisfied(1, second);
	ResultInfo::GetInstance().SetIsSatisfied(2, third);
}
