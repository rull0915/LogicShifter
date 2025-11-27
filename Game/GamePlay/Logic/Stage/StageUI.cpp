#include "StageUI.h"

#pragma region StageUI

StageUI::StageUI(StageData& stageData)
	: m_button{ { BUTTON_SIZE.x / 2, Screen::HEIGHT / 2}, BUTTON_SIZE, false, 0xEEEEEE }
	, m_nowState{ State::Hide }
	, m_position { -Screen::WIDTH * (2.0f / 5), 0 }
	, m_easingX{ 0 }
	, m_textInputManager{ &m_conditionString, {Screen::WIDTH * (1.0f / 5), 75} , {Screen::WIDTH * (1.0f / 3), 50}}
	, m_widthInput{ &m_widthStr, {Screen::WIDTH * (1.0f / 10), 150}, {100, 30} }
	, m_heightInput{ &m_heightStr, {Screen::WIDTH * (3.0f / 10), 150}, {100, 30} }
	, m_scrollHeight{ 0 }
	, m_inputNum{ 0 }
	, m_outputNum{ 0 }
	, m_stageData{ stageData }
{
	for(int i = 0; i < std::pow(2, Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_INPUT}]); i++)
	{
		m_settings.push_back(std::make_unique<Setting>(i));
	}
}

void StageUI::Initialize()
{
	m_textInputManager.Initialize();
	m_widthInput.Initialize(true);
	m_heightInput.Initialize(true);

	for (auto& setting : m_settings) setting->Initialize();
}

void StageUI::Update(float elapsedTime)
{
	// 開閉
	StateUpdate(elapsedTime);

	// スクロール
	if (PointIsOnMe({ static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y)}))
	{
		m_scrollHeight += MouseWheelRot() * 50;
	}

	if (m_scrollHeight > 0) m_scrollHeight = 0;
	if (m_scrollHeight < -(std::pow(2, m_inputNum) * Screen::HEIGHT * (1.0f / 4) - Screen::HEIGHT * (1.f / 2))) m_scrollHeight = -(std::pow(2, m_inputNum) * Screen::HEIGHT * (1.0f / 4) - Screen::HEIGHT * (1.f / 2));

	// 設定の更新
	if(m_inputNum > 0)
	for (int i = 0; i < std::pow(2, m_inputNum); i++)
	{
		float posY = m_position.y + Screen::HEIGHT * (1.0f / 2) + m_scrollHeight + i * Screen::HEIGHT * (1.0f / 4);

		m_settings[i]->ChangeInputNum(m_inputNum);
		m_settings[i]->ChangeOutputNum(m_outputNum);
		m_settings[i]->SetPos({ m_position.x + Screen::WIDTH * (1.0f / 5), posY });

		if(posY >= Screen::HEIGHT * (2.0f / 7)) m_settings[i]->Update(elapsedTime);
	}

	// テキストボックスの更新
	m_textInputManager.Update();
	m_widthInput.Update();
	m_heightInput.Update();

	m_textInputManager.SetPos({ m_position.x + (Screen::WIDTH * (1.0f / 5)), 75 });
	m_widthInput.SetPos({ m_position.x + (Screen::WIDTH * (1.0f / 10)), 150 });
	m_heightInput.SetPos({ m_position.x + (Screen::WIDTH * (3.0f / 10)), 150 });

	// ボタンの更新
	m_button.Update();
	m_button.ChengePos({ m_position.x + Screen::WIDTH * (2.f / 5) + BUTTON_SIZE.x / 2, Screen::HEIGHT / 2});

	// データの更新
	// 条件文
	m_stageData.SetConditionStr(m_conditionString);

	// 条件
	for (int i = 0; i < std::pow(2, m_inputNum); i++)
	{
		for (int j = 0; j < m_outputNum; j++) 
		{
			m_stageData.SetCondition(i, j, m_settings[i]->GetCondition(j));
		}
	}

	// ステージサイズ
	m_stageData.SetStageSize({ 
		(m_widthStr.size() > 0 ? std::stoi(m_widthStr) : 0), 
		(m_heightStr.size() > 0 ? std::stoi(m_heightStr) : 0)
	});
}

void StageUI::Render()
{
	// 背景の描画
	DrawBox(0, 0, m_position.x + Screen::WIDTH * (2.f / 5), Screen::HEIGHT, 0x333333, true);

	// 設定の描画
	if (m_inputNum > 0)
		for (int i = 0; i < std::pow(2, m_inputNum); i++)
		{
			float posY = m_position.y + Screen::HEIGHT * (1.0f / 2) + m_scrollHeight + i * Screen::HEIGHT * (1.0f / 4);

			if (posY >= Screen::HEIGHT * (2.0f / 7)) m_settings[i]->Render();
		}

	// 上部の描画
	DrawBox(0, 0, m_position.x + Screen::WIDTH * (2.f / 5), Screen::HEIGHT * (2.f / 7), 0x777777, true);

	// 入力ボックスの描画
	DrawFormatStringToHandle(m_position.x + (Screen::WIDTH * ((1.f / 5) - (1.f / 6))), m_position.y + 50 - 24, 0xffffff, GetFontHandle(24), L"条件文入力");
	DrawFormatStringToHandle(m_position.x + (Screen::WIDTH * (1.f / 10)) - (100 / 2), m_position.y + 135 - 16, 0xffffff, GetFontHandle(16), L"幅入力");
	DrawFormatStringToHandle(m_position.x + (Screen::WIDTH * (3.f / 10)) - (100 / 2), m_position.y + 135 - 16, 0xffffff, GetFontHandle(16), L"高さ入力");

	m_widthInput.Render();
	m_heightInput.Render();
	m_textInputManager.Render();

	// カーソルの描画
	float height = Screen::HEIGHT * ((m_scrollHeight) / (-(std::pow(2, m_inputNum) * Screen::HEIGHT * (1.0f / 4) - Screen::HEIGHT * (1.f / 2))));
	DrawCircle(m_position.x + 10, height, 10, 0xDDDDDD, true);

	// ボタンの描画
	m_button.Render();
}

bool StageUI::PointIsOnMe(Vector2D point)
{
	Vector2D buttonPos = m_button.GetPos();

	bool a = point.x > m_position.x && point.x < m_position.x + Screen::WIDTH * (2.0f / 5);
	bool b = (point.x > buttonPos.x - BUTTON_SIZE.x && point.x < buttonPos.x + BUTTON_SIZE.x) && (point.y > buttonPos.y - BUTTON_SIZE.y && point.y < buttonPos.y + BUTTON_SIZE.y);

	return a || b;
}

void StageUI::StateUpdate(float elapsedTime)
{
	// 状態により分岐
	switch (m_nowState)
	{
	case State::Opening:

		// イージング変数の加算
		m_easingX += elapsedTime;

		// 動かす
		m_position.x = -Screen::WIDTH * (2.f / 5) + (Screen::WIDTH * (2.0f / 5)) * Easing::EaseOutQuart(m_easingX);
		m_button.ChengePos({ m_position.x + Screen::WIDTH * (2.f / 5) + BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });

		if (m_easingX >= 1)
		{
			m_nowState = State::Exist;
			m_position.x = 0;
			m_button.ChengePos({ m_position.x + Screen::WIDTH * (2.f / 5) + BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });
		}

		break;
	case State::Closing:

		// イージング変数の加算
		m_easingX += elapsedTime;

		// 動かす
		m_position.x =  - (Screen::WIDTH * (2.0f / 5)) * Easing::EaseOutQuart(m_easingX);
		m_button.ChengePos({ m_position.x + Screen::WIDTH * (2.f / 5) + BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });

		if (m_easingX >= 1)
		{
			m_nowState = State::Hide;
			m_position.x = -Screen::WIDTH * (2.0f / 5);
			m_button.ChengePos({ m_position.x + Screen::WIDTH * (2.f / 5) + BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });
		}

		break;
	case State::Hide:

		// イージング初期化
		m_easingX = 0;

		// スライドボタンが押されたら
		if (m_button.GetIsPressed() && !(m_textInputManager.IsInputting() || m_widthInput.IsInputting() || m_heightInput.IsInputting()))
		{
			// 状態をオープンに
			m_nowState = State::Opening;
		}

		break;
	case State::Exist:

		// イージング初期化
		m_easingX = 0;

		// スライドボタンが押されたら
		if (m_button.GetIsPressed() && !(m_textInputManager.IsInputting() || m_widthInput.IsInputting() || m_heightInput.IsInputting()))
		{
			// 状態をクローズに
			m_nowState = State::Closing;
		}

		break;
	default:
		break;

	}
}

#pragma endregion

#pragma region Setting

Setting::Setting(int num)
	: m_inputs {}
	, m_outputs{}
	, m_switches{}
{
	m_inputs = new bool[Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_INPUT}]];
	m_outputs = new bool[Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_OUTPUT}]];

	// 数値を入力に変換
	for(int i = 0; i < Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_INPUT}]; i++)
	{
		m_inputs[i] = (num >> i) & 1;
	}
}

void Setting::Initialize()
{
	m_inputNum = 0;
	m_outputNum = 0;

	for (int i = 0; i < Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_OUTPUT}]; i++) m_outputs[i] = false;

	m_switches.clear();
	m_switches.resize(Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_OUTPUT}]);

	for (int i = 0; i < Cell::CELL_MAX_COUNT[{TYPE_OTHERS, SUBTYPE_OUTPUT}]; i++)
	{
		m_switches[i] = std::make_unique<Switch>(m_outputs[i], Vector2D{ m_position.x, m_position.y }, Vector2D{ 60, 30 });

		m_switches[i]->Initialize();
	}
}

void Setting::Update(float elapsedTime)
{
	for(int i = 0; i < m_outputNum; i++)
	{
		// 位置の変更
		Vector2D pos = { m_position.x - BOX_SIZE.x / 2 + (i + 1) * (BOX_SIZE.x / (m_outputNum + 1)), m_position.y};

		m_switches[i]->SetPos(pos);
	}

	for (int i = 0; i < m_outputNum; i++) m_switches[i]->Update(elapsedTime);
}

void Setting::Render()
{
	// 出力枠の描画
	DrawBox(m_position.x - BOX_SIZE.x / 2, m_position.y - BOX_SIZE.y / 2, m_position.x + BOX_SIZE.x / 2, m_position.y + BOX_SIZE.y / 2, 0x444444, true);

	// スイッチの描画
	for (int i = 0; i < m_outputNum; i++)
	{
		m_switches[i]->Render();
		MyDrawExtendFormatStringToHandleToCenter(
			m_switches[i]->GetPos().x, m_switches[i]->GetPos().y + 30, 1, 1, 0xffffff, GetFontHandle(16), std::to_wstring(i + 1).c_str());
	}

	// 入力枠の描画
	// 位置
	std::pair<Vector2D, Vector2D> inputPos = {
		Vector2D{ m_position.x - BOX_SIZE.x / 2 - BOX_SIZE.x / 10, m_position.y - BOX_SIZE.y / 2 - BOX_SIZE.y * (2.0f / 3)},
		Vector2D{ m_position.x, m_position.y - BOX_SIZE.y / 2 + BOX_SIZE.y / 10}
	};
	DrawBox(inputPos.first.x, inputPos.first.y, inputPos.second.x, inputPos.second.y, 0x999999, true);


	// 入力の描画
	Vector2D inputSize = inputPos.second - inputPos.first;

	int fontHandle = GetFontHandle(static_cast<int>(inputSize.y * (1.0f / 2)));

	for (int i = 0; i < m_inputNum; i++)
	{
		// 位置の変更
		Vector2D pos = { inputPos.first.x + (i + 1) * (inputSize.x / (m_inputNum + 1)), inputPos.first.y + inputSize.y / 2 };

		const TCHAR* str = m_inputs[i] ? L"O" : L"X";

		MyDrawFormatStringToHandleToCenter(pos.x, pos.y, 0x000000, fontHandle, str);

		MyDrawFormatStringToHandleToCenter(
			pos.x, pos.y + 20, 0x222222, GetFontHandle(16), std::to_wstring(i + 1).c_str());
	}
}

#pragma endregion
