#include "CircuitEditer.h"
#include "SelectUI.h"

SelectUI::SelectUI(CircuitEditer* pParent)
	: m_pParent{ pParent }
	, m_nowState{ State::Hide }
	, m_easingX{ 0 }
	, m_position{ Screen::WIDTH, 0 }
	, m_slideButton{ {Screen::WIDTH - BUTTON_SIZE.x / 2, Screen::HEIGHT / 2}, BUTTON_SIZE, false, 0xEEEEEE }
	, m_buttons{}
	, m_blockExButton{}
	, m_colorPallet{}
	, m_blockButtons{}
{
}


void SelectUI::Initialize(PlayMode playMode)
{
	for (auto name : BUTTON_NAMES[playMode])
	{
		Button button(m_position, { 80, 80 }, true, m_ghIcons[buttonExplains[name].first]);
		m_buttons[name] = std::make_unique<Button>(std::move(button));
	}

	// ブロック選択ボタンの追加
	for (int i = 0; i < Cell::BUTTONS[playMode].size(); i++)
	{
		Button button({ m_position.x + 200 + 70 * (i % 4), m_position.y + 200 + 70 * (i / 4) }, { 60, 60 }, false, Cell::COLORS[Cell::BUTTONS[playMode][i]]);
		Button signalButton({ m_position.x + 200 + 70 * (i % 4), m_position.y + 200 + 70 * (i / 4) }, { 30, 30 }, false, Cell::ON_SIGNAL_COLORS[Cell::BUTTONS[playMode][i]]);

		m_blockButtons[Cell::BUTTONS[playMode][i]] = { std::make_unique<Button>(std::move(button)), std::make_unique<Button>(std::move(signalButton)) };
	}
	
	// ブロック説明用ボタンの追加
	Button blockEx = Button({ m_position + Vector2D{100, 80} }, { 80, 80 }, true, m_ghIcons["Block"]);
	m_blockExButton = std::make_unique<Button>(std::move(blockEx));
}

void SelectUI::Update(float elapsedTime)
{
	// ボタンの更新
	m_slideButton.Update();
	m_blockExButton->Update();

	StateUpdate(elapsedTime);

	m_textBox.Update(false, { 0, 0 }, L"");

	m_blockExButton->ChengePos(m_position + Vector2D{ 100, 80 });
	if (m_blockExButton->MouseIsOnButton()) m_textBox.Update(true, { m_mousePos.x + 0.f, m_mousePos.y + 0.f }, blockExplain);

	int index = 0;
	// 保存ボタンの更新
	for (auto& button : m_buttons)
	{
		button.second->Update();

		button.second->ChengePos({ m_position.x + 100 + 100 * (index % 4), m_position.y + 400 + 100 * (index / 4) });

		if(button.second->MouseIsOnButton())
		{
			m_textBox.Update(true, { m_mousePos.x + 0.f, m_mousePos.y + 0.f }, buttonExplains[button.first].second);
		}

		// カラーパレットがアクティブじゃなくボタンが押されたら
		if (!m_colorPallet.GetIsActive() && button.second->GetIsPressed())
		{
			switch (button.first)
			{
			case Function::Save:

				m_pParent->SaveCells(SaveFileDialog());
				
				break;
			case Function::Load:
				
				m_pParent->LoadCells(LoadFileDialog());
				
				break;
			case Function::Reset:
				
				m_pParent->ChangePutMode(CircuitEditer::PutMode::Put);
				
				break;
			case Function::Copy:
				
				m_nowState = State::Closing;
				m_easingX = 0;

				m_pParent->ChangePutMode(CircuitEditer::PutMode::Copy);
				
				break;
			case Function::Paste:
				
				m_nowState = State::Closing;
				m_easingX = 0;

				m_pParent->ChangePutMode(CircuitEditer::PutMode::Paste);
				
				break;
			case Function::Range:
				
				m_nowState = State::Closing;
				m_easingX = 0;

				m_pParent->ChangePutMode(CircuitEditer::PutMode::Range);
				
				break;
			case Function::Vertical:
				
				m_nowState = State::Closing;
				m_easingX = 0;

				m_pParent->CopyInversion(false);
				
				break;
			case Function::Horizontal:
				
				m_nowState = State::Closing;
				m_easingX = 0;

				m_pParent->CopyInversion(true);
				
				break;
			case Function::Clear:

				m_pParent->Reset();

				break;
			case Function::Undo:
				
				m_pParent->Undo();
				
				break;
			case Function::Redo:
				m_pParent->Redo();
				break;
			default:
				break;
			}
		}

		index++;
	}

	// ブロック選択ボタンの更新
	index = 0;
	for(auto& button : m_blockButtons)
	{
		// 更新
		button.second.first->Update();
		button.second.second->Update();

		// 位置の変更
		button.second.first->ChengePos({ m_position.x + 180 + 80 * (index % 4), m_position.y + 120 + 80 * (index / 4) });
		button.second.first->ChengeColor(Cell::COLORS[button.first]);

		// 信号点灯時ボタンの位置の変更
		Vector2D p = { button.second.first->GetPos().x + 20, button.second.first->GetPos().y + 20 };
		button.second.second->ChengePos(p);
		button.second.second->ChengeColor(Cell::ON_SIGNAL_COLORS[button.first]);

		// ボタンが左クリックされたら
		if (button.second.first->GetIsPressed() && !m_colorPallet.GetIsActive())
		{
			PackedCell cell = 0;
			SetType(cell, button.first.first);
			SetSubType(cell, button.first.second);
			m_pParent->ChangePutCell(cell);
		}

		// 点灯時ボタンが右クリックされたら
		if (button.second.second->GetIsPressedRight() && !m_colorPallet.GetIsActive())
		{
			Vector2D pos = { static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) };

			if (m_mousePos.x > Screen::WIDTH * (3.0f / 4)) pos.x -= ColorPallet::SIZE.x;

			// カラーパレットを出現
			m_colorPallet.Initialize(pos, &Cell::ON_SIGNAL_COLORS[button.first]);
		}
		// 通常時ボタンが右クリックされたら
		else if (button.second.first->GetIsPressedRight() && !m_colorPallet.GetIsActive())
		{
			Vector2D pos = { static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) };

			if (m_mousePos.x > Screen::WIDTH * (3.0f / 4)) pos.x -= ColorPallet::SIZE.x;

			// カラーパレットを出現
			m_colorPallet.Initialize(pos, &Cell::COLORS[button.first]);
		}

		// ボタン上にマウスがあれば
		if (button.second.first->MouseIsOnButton())
		{
			Vector2DInt pos;
			GetMousePoint(&pos.x, &pos.y);
			m_textBox.Update(true, { pos.x + 0.f, pos.y + 0.f }, blockButtonExplains[button.first]);
		}

		// 加算
		index++;
	}

	// カラーパレットの更新
	m_colorPallet.Update();
}

void SelectUI::Render()
{
	// ボタンの描画
	m_slideButton.Render();

	DrawBoxAA(m_position.x, m_position.y, Screen::WIDTH, Screen::HEIGHT, 0x333333, true);

	for (auto& button : m_buttons) button.second->Render();
	for (auto& button : m_blockButtons)
	{
		button.second.first->Render();
		button.second.second->Render();
	}

	m_blockExButton->Render();

	if(m_nowState == State::Exist) m_textBox.Render(false);

	// カラーパレットの描画
	m_colorPallet.Render();
}

bool SelectUI::GetInSelectUI(Vector2DInt screenPos)
{
	Vector2D buttonPos = m_slideButton.GetPos();

	bool a = (screenPos.x > m_position.x && screenPos.x < Screen::WIDTH) && (screenPos.y > m_position.y && screenPos.y < Screen::HEIGHT);
	bool b = (screenPos.x > buttonPos.x - BUTTON_SIZE.x && screenPos.x < buttonPos.x + BUTTON_SIZE.x) && (screenPos.y > buttonPos.y - BUTTON_SIZE.y && screenPos.y < buttonPos.y + BUTTON_SIZE.y);

	bool c = (m_nowState == State::Closing || m_nowState == State::Opening);
	bool d = m_colorPallet.GetMouseOnThis(screenPos);

	return a || b || c || d;
}

void SelectUI::SetState(State state)
{
	switch (state)
	{
		// 遷移後が開き中なら
	case State::Opening:
		// 隠れていなければ無視
		if (m_nowState != State::Hide) return;
		m_nowState = State::Opening;
		break;
	case State::Closing:
		// 遷移後が閉じ中なら
		if (m_nowState != State::Exist) return;
		m_nowState = State::Closing;
		break;
	case State::Hide:
		// 遷移後が隠しなら
		if (m_nowState == State::Exist) m_nowState = State::Closing;
		break;
	case State::Exist:
		// 遷移後が存在したら
		if (m_nowState == State::Hide) m_nowState = State::Opening;
		break;
	default:
		break;
	}
}

void SelectUI::StateUpdate(float elapsedTime)
{
	// 状態により分岐
	switch (m_nowState)
	{
	case State::Opening:

		// イージング変数の加算
		m_easingX += elapsedTime;

		// 動かす
		m_position.x = Screen::WIDTH - (Screen::WIDTH * (2.0f / 5)) * Easing::EaseOutQuart(m_easingX);
		m_slideButton.ChengePos({ m_position.x - BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });

		if (m_easingX >= 1)
		{
			m_nowState = State::Exist;
			m_position.x = (Screen::WIDTH * (3.0f / 5));
			m_slideButton.ChengePos({ m_position.x - BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });
		}

		break;
	case State::Closing:

		// イージング変数の加算
		m_easingX += elapsedTime;

		// 動かす
		m_position.x = Screen::WIDTH * (3.0f / 5) + (Screen::WIDTH * (2.0f / 5)) * Easing::EaseOutQuart(m_easingX);
		m_slideButton.ChengePos({ m_position.x - BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });

		if (m_easingX >= 1)
		{
			m_nowState = State::Hide;
			m_position.x = Screen::WIDTH;
			m_slideButton.ChengePos({ m_position.x - BUTTON_SIZE.x / 2, Screen::HEIGHT / 2 });
		}

		break;
	case State::Hide:

		// イージング初期化
		m_easingX = 0;

		// スライドボタンが押されたら
		if (m_slideButton.GetIsPressed())
		{
			// 状態をオープンに
			m_nowState = State::Opening;
		}

		break;
	case State::Exist:

		// イージング初期化
		m_easingX = 0;

		// スライドボタンが押されたら
		if (m_slideButton.GetIsPressed())
		{
			// 状態をクローズに
			m_nowState = State::Closing;
		}

		break;
	default:
		break;
	}
}
