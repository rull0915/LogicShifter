#include "FreeManager.h"

FreeManager::FreeManager()
	: ModeManager()
	, m_circuitEditer{ m_cells, m_cameraPos, m_cameraScale }
	, m_circuitSimulator{ m_cells, m_nextCells }
	, m_playButtons{}
	, m_textBox{}
	, m_nowElapsedTime{ 0 }
	, m_playSpeed{ INT_MAX + 0.f }
{
}

FreeManager::~FreeManager()
{
}

void FreeManager::Initialize()
{
	STAGE_WIDTH = 300;
	STAGE_HEIGHT = 300;

	OFFSET_X = STAGE_WIDTH / 2;
	OFFSET_Y = STAGE_HEIGHT / 2;

	// サイズ確保
	m_cells.clear();
	m_nextCells.clear();

	m_cells.resize(STAGE_WIDTH * STAGE_HEIGHT + 1);
	m_nextCells.resize(STAGE_WIDTH * STAGE_HEIGHT + 1);
	std::fill(m_cells.begin(), m_cells.end(), 0);
	std::fill(m_nextCells.begin(), m_nextCells.end(), 0);

	m_circuitSimulator.Initialize();
	m_circuitEditer.Initialize(PlayMode::Free);

	// ボタンの追加
	for (auto button : buttonInfos)
	{
		auto b = Button(button.second.first, BUTTON_SIZE, true, m_ghIcons[button.first]);
		m_playButtons[button.first] = std::make_unique<Button>(std::move(b));
	}
}

void FreeManager::Update(float elapsedTime)
{
	if (MouseEnter() & MOUSE_INPUT_MIDDLE)
	{
		m_cameraPos += { static_cast<float>(GetMouseMoveValue().x), static_cast<float>(GetMouseMoveValue().y) };

		m_mouseDrawMode = MouseMode::Move;
	}

	ChangeScale(m_cameraScale - static_cast<float>(MouseWheelRot()) / 5);


	// ボタン上にないか
	bool mouseIsOnButton = false;
	for (auto& button : m_playButtons) if (button.second->MouseIsOnButton()) mouseIsOnButton = true;


	// エディタの更新
	m_circuitEditer.Update(elapsedTime);

	// ボタン上になく、UI上になかったら
	if (!mouseIsOnButton && !m_circuitEditer.PointIsOnUI({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) }))
	{
		// 実行中だったら
		if (m_playSpeed < INT_MAX)
		{
			m_circuitSimulator.Update(m_cameraPos, 1.0f / m_cameraScale);
		}
		// 実行中じゃなかったら
		else m_circuitEditer.CellUpdate();
	}

	float cameraScale = (1.0f / m_cameraScale);

	m_textBox.Update(false, { -1, -1 }, L"");
	// ボタンの更新
	for (auto& button : m_playButtons)
	{
		button.second->Update();

		// ボタンが押されたときの処理
		if (button.second->GetIsPressed())
		{
			if (button.first == "Play")
			{
				m_playSpeed = UPDATE_DISTANCE_FAST;
				m_circuitEditer.ChangeUIState(State::Closing);
			}
			else if (button.first == "PlayFast")
			{
				m_playSpeed = UPDATE_DISTANCE_FASTTEST;
				m_circuitEditer.ChangeUIState(State::Closing);
			}
			else if (button.first == "Stop")m_playSpeed = INT_MAX + 0.f;
			else if (button.first == "PlayOnce")
			{
				m_playSpeed = INT_MAX + 0.f;
				m_circuitSimulator.ToNextCells();
			}

			m_nowElapsedTime = 0;
		}

		if (button.second->MouseIsOnButton())
		{
			m_textBox.Update(true, { m_mousePos.x + 0.f, m_mousePos.y + 0.f }, buttonInfos[button.first].second);
		}
	}

	// 時間の加算
	m_nowElapsedTime += elapsedTime;

	if (m_nowElapsedTime > m_playSpeed)
	{
		if(m_playSpeed == UPDATE_DISTANCE_FASTTEST)
		{
			for(int i = 0; i < 10; i++) m_circuitSimulator.ToNextCells();
		}
		else m_circuitSimulator.ToNextCells();

		m_nowElapsedTime = 0;
	}
}

void FreeManager::Render()
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
	DrawBox(30, 30, 290, 110, 0x444444, true);

	// ボタンの描画
	for (auto& button : m_playButtons) button.second->Render();
}

void FreeManager::Finalize()
{
	m_circuitEditer.Finalize();

	for (auto& button : m_playButtons) button.second->Finalize();
}
