#include "BaseTutorial.h"
#include "../Game/Common/MaskManager.h"

#pragma region Once

OnceTutorial::OnceTutorial(Vector2D pos, Vector2D size, const std::wstring& explainStr, Vector2D drawSize)
	: m_position{ pos }
	, m_size{ size }
	, m_explainStr{ explainStr }
	, m_drawSize{ drawSize }
	, m_isEnd{ false }
{
}

void OnceTutorial::Update()
{
	static bool isPressed = false;

	// クリックされたら
	if (MouseDown() & MOUSE_INPUT_LEFT)
	{
		// マウスが自分の上にあれば
		if (OnMe())
		{
			isPressed = true;
		}
		else isPressed = false;
	}

	// クリックを離したら
	if (MouseUp() & MOUSE_INPUT_LEFT)
	{
		// 押されたフラグがtrueなら
		if(OnMe() && isPressed) m_isEnd = true;
	}
}

void OnceTutorial::Render()
{
	// マスクの描画
	MaskManager::GetInstance().StartDrawMask();

	DrawBox(m_position.x - m_drawSize.x / 2, m_position.y - m_drawSize.y / 2, m_position.x + m_drawSize.x / 2, m_position.y + m_drawSize.y / 2, 0, true);

	MaskManager::GetInstance().FinishDrawMask();

	// マスクのセット
	MaskManager::GetInstance().SetMask(false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	// 描画
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// マスクの終了
	MaskManager::GetInstance().CancelMask();

	// 矢印の描画
	if(m_position.x < Screen::WIDTH / 2)
	{
		DrawExtendGraph(m_position.x + m_drawSize.x / 2 + 5, m_position.y + m_drawSize.y / 2 + 5, m_position.x + m_drawSize.x / 2 + 69, m_position.y + m_drawSize.y / 2 + 69, m_ghIcons["ArrowLU"], true);
	}
	else
	{
		DrawExtendGraph(m_position.x - m_drawSize.x / 2 - 69, m_position.y + m_drawSize.y / 2 + 5, m_position.x - m_drawSize.x / 2 - 5, m_position.y + m_drawSize.y / 2 + 69, m_ghIcons["ArrowRU"], true);
	}

	// 説明の描画
	DrawBox(Screen::WIDTH * (2.0f / 8), Screen::HEIGHT * (25.0f / 32), Screen::WIDTH * (6.0f / 8), Screen::HEIGHT * (29.0f / 32), 0xAAAAAA, true);

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH / 2, Screen::HEIGHT * (27.0f / 32), 0x000000, GetFontHandle(Screen::HEIGHT * (1.0f / 24)), m_explainStr.c_str());
}

bool OnceTutorial::OnMe()
{
	if (m_size.x == 0 && m_size.y == 0) return true;

	return (
		(m_mousePos.x >= m_position.x - m_size.x / 2 && m_mousePos.x <= m_position.x + m_size.x / 2) &&
		(m_mousePos.y >= m_position.y - m_size.y / 2 && m_mousePos.y <= m_position.y + m_size.y / 2) 
		);
}

#pragma endregion

#pragma region Tutorial

void Tutorial::Initialize(TutorialType type)
{
	m_isActive = true;

	switch (type)
	{
	case TutorialType::None:

		m_isActive = false;

		break;

	case TutorialType::Start:

		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 - 96, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"クリックでブロックを置くことができます", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 - 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"クリックでブロックを置くことができます", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"クリックでブロックを置くことができます", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 96, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"クリックでブロックを置くことができます", Vector2D{ 80, 80 }));

		m_tutorials.push(OnceTutorial(Vector2D{ 70, 70 }, Vector2D{ 60, 60 }, L"ボタンを押すと作成した回路を実行できます", Vector2D{ 70, 70 }));

		break;

	case TutorialType::Operation:

		m_tutorials.push(OnceTutorial(Vector2D{ 7000, 70 }, Vector2D{ 0, 0 }, L"右クリックでブロックを消すことができます", Vector2D{ 0, 0 }));
		m_tutorials.push(OnceTutorial(Vector2D{ 7000, 70 }, Vector2D{ 0, 0 }, L"中クリックで移動ができます", Vector2D{ 0, 0 }));

		break;

	case TutorialType::Select:

		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH - 8, Screen::HEIGHT / 2 }, Vector2D{ 16, 32 }, L"ボタンをクリックするとUIが出ます", Vector2D{ 24, 48 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH * (3.0f / 5) + 260, 0 + 120 }, Vector2D{ 60, 60 }, L"クリックで置くブロックを変更できます", Vector2D{ 70, 70 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH * (3.0f / 5) + 260, 0 + 120 }, Vector2D{ 0, 0 }, L"今回は信号の交差が可能な\nCrossブロックを使ってみます", Vector2D{ 0, 0 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH * (3.0f / 5) - 8, Screen::HEIGHT / 2 }, Vector2D{ 16, 32 }, L"もう一度クリックするとUIを隠せます", Vector2D{ 24, 48 }));

		break;

	case TutorialType::And:

		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"And演算ブロックです", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"　　周囲4マスにある全てのWireから\n信号を受け取っていると、信号を出力します", Vector2D{ 80, 80 }));

		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 96, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"OutPutブロックです", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 96, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"隣接するAndの出力を受け取ることができます", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 96, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"受け取った出力をWireに与えます", Vector2D{ 80, 80 }));

		break;

	case TutorialType::Or:

		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"Or演算ブロックです", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"　　周囲4マスにあるどれかのWireから\n信号を受け取っていると、信号を出力します", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"Andと同じくOutPutに信号を出力します", Vector2D{ 80, 80 }));

		break;

	case TutorialType::Not:

		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"Not演算ブロックです", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"OutPutのようにAnd,Orの出力を受け取ります", Vector2D{ 80, 80 }));
		m_tutorials.push(OnceTutorial(Vector2D{ Screen::WIDTH / 2 + 32, Screen::HEIGHT / 2 + 32 }, Vector2D{ 64, 64 }, L"受け取った出力を反転し、出力します", Vector2D{ 80, 80 }));

		break;

	default:
		break;
	}
}

void Tutorial::Update()
{
	// 非アクティブならスキップ
	if (!m_isActive) return;

	m_isClicked = false;

	m_tutorials.front().Update();

	if (m_tutorials.front().GetIsEnd())
	{
		m_tutorials.pop();

		m_isClicked = true;
	}

	if (m_tutorials.size() == 0)
	{
		m_isActive = false;
	}
}

void Tutorial::Render()
{
	if (!m_isActive) return;

	m_tutorials.front().Render();
}

void Tutorial::Finalize()
{
}

#pragma endregion
