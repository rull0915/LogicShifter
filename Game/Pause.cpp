#include "Pause.h"
#include "../Game/Game.h"
#include "GamePlay/Logic/ResultInfo.h"
#include "Common/MaskManager.h"

Pause::Pause(Game* pGame)
	: Scene( pGame->GetSceneManager() )
 	, m_nowState{ State::None }
	, m_isActive{ false }
	, m_resume		{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (3.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x3762AF }
	, m_retry		{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (4.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x3762AF }
	, m_stageSelect	{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (5.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x3762AF }
	, m_modeSelect	{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (6.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x3762AF }
	, m_option		{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (6.0f / 8)}, Vector2D{ Screen::WIDTH * (5.0f / 19), Screen::HEIGHT / 13}, false, 0x3762AF }

	, m_invalidResume		{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (3.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x595959 }
	, m_invalidRetry		{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (4.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x595959 }
	, m_invalidStageSelect	{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (5.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x595959 }
	, m_invalidModeSelect	{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (6.0f / 8)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x595959 }
	, m_invalidOption		{ Vector2D{Screen::WIDTH / 2, Screen::HEIGHT * (6.0f / 8)}, Vector2D{ Screen::WIDTH * (5.0f / 19), Screen::HEIGHT / 13}, false, 0x595959}

	, m_cursorPos{ 0 }
	, m_setting{}
{
}

void Pause::Initialize(State state)
{
	m_nowState = state;

	m_isActive = true;

	m_resume.Initialize();
	m_retry.Initialize();
	m_stageSelect.Initialize();
	m_modeSelect.Initialize();

	m_invalidResume.Initialize();
	m_invalidRetry.Initialize();
	m_invalidStageSelect.Initialize();
	m_invalidModeSelect.Initialize();

	m_setting.Initialize();

	switch (m_nowState)
	{
	case Pause::State::StageMode:

		m_resume.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (20.0f / 54) });
		m_retry.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (25.0f / 54) });
		m_stageSelect.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (30.0f / 54) });
		m_modeSelect.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (35.0f / 54) });
		m_option.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (42.0f / 54) });

		m_invalidResume.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (20.0f / 54) });
		m_invalidRetry.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (25.0f / 54) });
		m_invalidStageSelect.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (30.0f / 54) });
		m_invalidModeSelect.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (35.0f / 54) });
		m_invalidOption.ChengePos(Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT * (42.0f / 54) });

		break;
	case Pause::State::OtherMode:
	case Pause::State::StageSelect:
	case Pause::State::Others:

		m_resume.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (20.0f / 54) });
		m_retry.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (25.0f / 54) });
		m_stageSelect.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (30.0f / 54) });
		m_modeSelect.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (35.0f / 54) });
		m_option.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (42.0f / 54) });

		m_invalidResume.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (20.0f / 54) });
		m_invalidRetry.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (25.0f / 54) });
		m_invalidStageSelect.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (30.0f / 54) });
		m_invalidModeSelect.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (35.0f / 54) });
		m_invalidOption.ChengePos(Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (42.0f / 54) });

		break;
	default:
		break;
	}

	m_cursorPos = 0;
}

void Pause::Update(float elapsedTime)
{
	if (!m_isActive) return;

	// オプションボタンの更新
	m_option.Update();

	if(m_option.GetIsPressed())
	{
		m_setting.SetIsActive(true);
	}

	m_setting.Update(elapsedTime);

	if (m_setting.GetIsActive()) return;

	// ボタンの更新
	switch (m_nowState)
	{
	case Pause::State::StageMode:

		m_resume.Update();
		m_retry.Update();
		m_stageSelect.Update();
		m_modeSelect.Update();

		// カーソルの移動
		CursorUpdate();

		break;
	case Pause::State::OtherMode:
	case Pause::State::StageSelect:

		m_resume.Update();
		m_invalidRetry.Update();
		m_invalidStageSelect.Update();
		m_modeSelect.Update();

		break;

	case Pause::State::Others:

		m_resume.Update();
		m_invalidRetry.Update();
		m_invalidStageSelect.Update();
		m_invalidModeSelect.Update();

		break;

		break;
	default:
		break;
	}

	if (m_resume.GetIsPressed())
	{
		m_isActive = false;
	}
	if (m_retry.GetIsPressed())
	{
		m_isActive = false;
		ChangeScene(
			"GamePlay",
			std::make_unique<ClockTransition>(0.5f, Transition::Mode::In, 0x333F50),
			std::make_unique<ClockTransition>(0.5f, Transition::Mode::Out, 0x333F50)
		);
	}
	if (m_stageSelect.GetIsPressed())
	{
		m_isActive = false;
		ChangeScene(
			"Select",
			std::make_unique<BlocksTransition>(1.0f, Transition::Mode::In, 0x333F50, Vector2D{ 0, 0 }, Vector2DInt{ 8, 5 }),
			std::make_unique<BlocksTransition>(1.0f, Transition::Mode::Out, 0x333F50, Vector2D{ 0, 0 }, Vector2DInt{ 8, 5 })
		);
	}
	if (m_modeSelect.GetIsPressed())
	{
		m_isActive = false;
		ChangeScene(
			"ModeSelect",
			std::make_unique<BlocksTransition>(1.0f, Transition::Mode::In, 0x333F50, Vector2D{ 0, 0 }, Vector2DInt{ 8, 5 }),
			std::make_unique<BlocksTransition>(1.0f, Transition::Mode::Out, 0x333F50, Vector2D{ 0, 0 }, Vector2DInt{ 8, 5 })
		);
	}
}

void Pause::Render()
{
	if (!m_isActive) return;

	// 画面を暗く
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ポーズ中の文字列
	MyDrawRoundBoxAA({ Screen::WIDTH * (1.0f / 4), Screen::HEIGHT * (1.0f / 16) }, { Screen::WIDTH * (3.0f / 4), Screen::HEIGHT * (3.0f / 16) }, 10, 0xAAAAAA, true);

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH / 2, Screen::HEIGHT / 8, 0x000000, GetFontHandle(Screen::HEIGHT / 12), L"ポーズ中");

	// ボタン達の背景
	DrawBox(
		m_resume.GetPos().x - Screen::WIDTH / 6, Screen::HEIGHT * (2.0f / 7),
		m_resume.GetPos().x + Screen::WIDTH / 6, Screen::HEIGHT * (6.0f / 7),
		0x333333, true
	);

	m_option.Render();
	MyDrawFormatStringToHandleToCenter(m_option.GetPos().x, m_option.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 22), L"Setting");

	// 描画
	switch (m_nowState)
	{
	case Pause::State::StageMode:

		m_resume.Render();
		m_retry.Render();
		m_stageSelect.Render();
		m_modeSelect.Render();

		DrawStageInfo();

		break;
	case Pause::State::OtherMode:
	case Pause::State::StageSelect:

		m_resume.Render();
		m_invalidRetry.Render();
		m_invalidStageSelect.Render();
		m_modeSelect.Render();

		break;

	case Pause::State::Others:

		m_resume.Render();
		m_invalidRetry.Render();
		m_invalidStageSelect.Render();
		m_invalidModeSelect.Render();

		break;

		break;
	default:
		break;
	}

	MyDrawFormatStringToHandleToCenter(m_resume.GetPos().x, m_resume.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"Resume");
	MyDrawFormatStringToHandleToCenter(m_retry.GetPos().x, m_retry.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"Retry");
	MyDrawFormatStringToHandleToCenter(m_stageSelect.GetPos().x, m_stageSelect.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"StageSelect");
	MyDrawFormatStringToHandleToCenter(m_modeSelect.GetPos().x, m_modeSelect.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"ModeSelect");

	m_setting.Render();
}

void Pause::Finalize()
{
}

void Pause::DrawStageInfo()
{
	// 背景
	DrawBox(Screen::WIDTH * (9.0f / 16), Screen::HEIGHT * (2.0f / 8), Screen::WIDTH * (15.0f / 16), Screen::HEIGHT * (15.0f / 16), 0x333333, true);

	// ステージ名の描画
	DrawFormatStringToHandle(Screen::WIDTH * (19.0f / 32), Screen::HEIGHT * (2.0f / 7), 0xffffff, GetFontHandle(Screen::HEIGHT / 24), (ResultInfo::GetInstance().GetStageName()).c_str());

	DrawLine(Screen::WIDTH * (9.0f / 16) + 20, Screen::HEIGHT * (1.0f / 3), Screen::WIDTH * (15.0f / 16) - 20, Screen::HEIGHT * (1.0f / 3), 0xffffff);

	// 条件

	// 入出力文字列
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (21.0f / 32), Screen::HEIGHT * (3.0f / 8), 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"入力");
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (24.0f / 32), Screen::HEIGHT * (3.0f / 8) - 10, 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"条件");
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (27.0f / 32), Screen::HEIGHT * (3.0f / 8), 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"出力");

	const std::vector<Condition>& conditions = ResultInfo::GetInstance().GetConditions();

	std::wstring inputNum = L"", outputNum = L"";
	if (conditions.size() > 0) 
	{
		for (int i = 0; i < conditions[0].inputs.size(); i++)
		{
			inputNum += std::to_wstring(i + 1);

			if ((i + 1) < conditions[0].inputs.size()) inputNum += L"  ";
		}
		for (int i = 0; i < conditions[0].outputs.size(); i++)
		{
			outputNum += std::to_wstring(i + 1);

			if ((i + 1) < conditions[0].outputs.size()) outputNum += L"  ";
		}
	}

	// 入出力数
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (21.0f / 32), Screen::HEIGHT * (5.0f / 12), 0xffffff, GetFontHandle(Screen::HEIGHT / 36), inputNum.c_str());
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (27.0f / 32), Screen::HEIGHT * (5.0f / 12), 0xffffff, GetFontHandle(Screen::HEIGHT / 36), outputNum.c_str());

	// 線
	DrawLine(Screen::WIDTH * (19.0f / 32), Screen::HEIGHT * (7.0f / 16), Screen::WIDTH * (23.0f / 32), Screen::HEIGHT * (7.0f / 16), 0xffffff);
	DrawLine(Screen::WIDTH * (25.0f / 32), Screen::HEIGHT * (7.0f / 16), Screen::WIDTH * (29.0f / 32), Screen::HEIGHT * (7.0f / 16), 0xffffff);

	DrawLine(Screen::WIDTH * (3.0f / 4), Screen::HEIGHT * (3.0f / 8), Screen::WIDTH * (3.0f / 4), Screen::HEIGHT * (29.0f / 32), 0xffffff);

	// 入力を文字列に
	std::wstring input = L"", output = L"";

	// マスク領域の設定
	MaskManager::GetInstance().StartDrawMask();
	DrawBox(Screen::WIDTH * (9.0f / 16), Screen::HEIGHT * (7.0f / 16), Screen::WIDTH * (15.0f / 16), Screen::HEIGHT * (29.0f / 32), 0x333333, true);
	MaskManager::GetInstance().FinishDrawMask();

	MaskManager::GetInstance().SetMask(true);

	for(int i = 0; i < conditions.size(); i++)
	{
		input = L"";
		output = L"";

		for (int j = 0; j < conditions[i].inputs.size(); j++)
		{
			input += (conditions[i].inputs[j] ? L"O" : L"X");

			if ((j + 1) < conditions[i].inputs.size()) input += L" ";
		}
		for (int j = 0; j < conditions[i].outputs.size(); j++)
		{
			output += (conditions[i].outputs[j] ? L"O" : L"X");

			if ((j + 1) < conditions[i].outputs.size()) output += L" ";
		}

		MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (21.0f / 32), Screen::HEIGHT * (5.0f / 12) + (i + 1) * (Screen::HEIGHT / 24) - m_cursorPos, 0xffffff, GetFontHandle(Screen::HEIGHT / 36), input.c_str());
		MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (27.0f / 32), Screen::HEIGHT * (5.0f / 12) + (i + 1) * (Screen::HEIGHT / 24) - m_cursorPos, 0xffffff, GetFontHandle(Screen::HEIGHT / 36), output.c_str());
	}

	MaskManager::GetInstance().CancelMask();
}

void Pause::CursorUpdate()
{
	// 範囲外なら実行しない
	if (!((m_mousePos.x >= Screen::WIDTH * (9.0f / 16) && m_mousePos.x <= Screen::WIDTH * (15.0f / 16)) &&
		(m_mousePos.y >= Screen::HEIGHT * (7.0f / 16) && m_mousePos.y <= Screen::HEIGHT * (29.0f / 32))))
	{
		return;
	}

	// 画面からはみ出していたら
	if (Screen::HEIGHT * (5.0f / 12) + ResultInfo::GetInstance().GetConditions().size() * (Screen::HEIGHT / 24) > Screen::HEIGHT * (29.0f / 32) + Screen::HEIGHT / 72)
	{
		m_cursorPos -= MouseWheelRot() * 10;

		if (m_cursorPos < 0) m_cursorPos = 0;

		if (m_cursorPos > ResultInfo::GetInstance().GetConditions().size() * (Screen::HEIGHT / 24) - Screen::HEIGHT * (5.0f / 12)) m_cursorPos = ResultInfo::GetInstance().GetConditions().size() * (Screen::HEIGHT / 24) - Screen::HEIGHT * (5.0f / 12);
	}
}
