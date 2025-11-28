#include "EditManager.h"
#include "Logic/CellRenderer.h"

EditManager::EditManager()
	: ModeManager()
	, m_circuitEditer{ m_cells, m_cameraPos, m_cameraScale }
	, m_stageUi{ m_stageData }
	, m_stageData{ m_cells }
	, m_canUpdate{ false }
	, m_saveButton{ {Screen::WIDTH / 2 + 50, 50 }, {75, 75}, true, m_ghIcons["Save"]}
{
}

EditManager::~EditManager()
{
}

void EditManager::Initialize()
{
	STAGE_WIDTH = 300;
	STAGE_HEIGHT = 300;

	OFFSET_X = STAGE_WIDTH / 2;
	OFFSET_Y = STAGE_HEIGHT / 2;

	m_stageUi.Initialize();

	m_resetButton.Initialize();

	// サイズ確保
	m_cells.resize(STAGE_WIDTH * STAGE_HEIGHT + 1);
	m_nextCells.resize(STAGE_WIDTH * STAGE_HEIGHT + 1);
	std::fill(m_cells.begin(), m_cells.end(), 0);
	std::fill(m_nextCells.begin(), m_nextCells.end(), 0);

	m_circuitEditer.Initialize(PlayMode::Edit);
}

void EditManager::Update(float elapsedTime)
{
	bool OnUI = 
		(m_stageUi.PointIsOnMe({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) }) || m_circuitEditer.PointIsOnUI({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) })) || m_resetButton.MouseIsOnButton() || m_saveButton.MouseIsOnButton();

	// カメラの移動
	if (!OnUI && MouseEnter() & MOUSE_INPUT_MIDDLE)
	{
		m_cameraPos += { static_cast<float>(GetMouseMoveValue().x), static_cast<float>(GetMouseMoveValue().y) };
	}

	// ステージ上でマウスが押されたら
	if (!OnUI && MouseDown() & MOUSE_INPUT_LEFT)
	{
		m_canUpdate = true;
	}
	else if (MouseDown() & MOUSE_INPUT_LEFT) m_canUpdate = false;

	// セルの更新
	if(m_canUpdate) m_circuitEditer.CellUpdate();

	if(!OnUI) ChangeScale(m_cameraScale - static_cast<float>(MouseWheelRot()) / 5);

	float cameraScale = (1.0f / m_cameraScale);

	// エディタの更新
	m_circuitEditer.Update(elapsedTime);

	// UIの更新
	m_stageUi.Update(elapsedTime);
	
	// todo
	// エディタからInput,Outputの数を取得しStageUIのChangeを呼ぶ
	m_stageUi.SetInputNum(m_circuitEditer.GetCellCount({ TYPE_OTHERS, SUBTYPE_INPUT }));
	m_stageUi.SetOutputNum(m_circuitEditer.GetCellCount({ TYPE_OTHERS, SUBTYPE_OUTPUT }));

	m_stageData.SetInputNum(m_circuitEditer.GetCellCount({ TYPE_OTHERS, SUBTYPE_INPUT }));
	m_stageData.SetOutputNum(m_circuitEditer.GetCellCount({ TYPE_OTHERS, SUBTYPE_OUTPUT }));

	m_stageData.SetInputInfo(m_circuitEditer.GetCellInfo({ TYPE_OTHERS, SUBTYPE_INPUT }));
	m_stageData.SetOutputInfo(m_circuitEditer.GetCellInfo({ TYPE_OTHERS, SUBTYPE_OUTPUT }));

	m_saveButton.Update();
	if (m_saveButton.GetIsPressed()) m_stageData.Save();

	m_resetButton.Update();
}

void EditManager::Render()
{
	// 背景描画
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, 0x111111, true);

	// セル
	CellRender();

	// グリッド
	GridRender();

	// ステージ範囲
	RangeRender(
		(Vector2DInt{ 0, 0 } - m_stageData.GetStageSize()) / 2, 
		{ Rounding(m_stageData.GetStageSize().x / 2.0f) - 1, Rounding(m_stageData.GetStageSize().y / 2.0f) - 1 },
		m_cameraPos, 1.0f / m_cameraScale, 0xDDDDDD);

	// 境界線
	BorderRender();

	// エディタの描画
	m_circuitEditer.Render();

	// UIの描画
	m_stageUi.Render();

	m_resetButton.Render();

	m_saveButton.Render();
}
