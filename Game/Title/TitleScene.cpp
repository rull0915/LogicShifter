#include "TitleScene.h"
#include "../Game/Game.h"
#include "../Game/Common/MaskManager.h"
#include "../Game/GamePlay/Logic/CellInfo.h"

TitleScene::TitleScene(Game* pGame)
	: Scene(pGame->GetSceneManager())
	, m_pGame(pGame)
	, m_startButton{ Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT / 2 + 40 }, Vector2D{ Screen::WIDTH / 6, Screen::HEIGHT / 18 }, false, 0x333333, true}
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	for(int i = 0; i < 36; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			m_backGround[i][j] = 0;
		}
	}

	m_backScreen = MakeScreen(64, 36);
}

void TitleScene::Update(float elapsedTime)
{
	m_startButton.Update();

	// 右クリックされたら
	if (m_startButton.GetIsPressed())
	{
		ChangeScene("ModeSelect",
			std::make_unique<IrisTransition>(1.0f, Transition::Mode::In, 0x1f1e33),
			std::make_unique<IrisTransition>(1.0f, Transition::Mode::Out, 0x1f1e33));
	}

	if (MouseEnter() & MOUSE_INPUT_LEFT)
	{
		Vector2DInt grid = ToGrid({(float)m_mousePos.x, (float)m_mousePos.y});

		if (!(grid.x < 0 || grid.x >= 64 || grid.y < 0 || grid.y >= 36))
		{
			if (m_backGround[grid.y][grid.x] == 0)
			{
				m_backGround[grid.y][grid.x] = GetRandColor();

				SetDrawScreen(m_backScreen);
				DrawPixel(grid.x, grid.y, m_backGround[grid.y][grid.x]);
				SetDrawScreen(DX_SCREEN_BACK);
			}
		}
	}

	else if (MouseEnter() & MOUSE_INPUT_RIGHT)
	{
		Vector2DInt grid = ToGrid({ (float)m_mousePos.x, (float)m_mousePos.y });

		if (!(grid.x < 0 || grid.x >= 64 || grid.y < 0 || grid.y >= 36))
		{
			if (m_backGround[grid.y][grid.x] != 0)
			{
				m_backGround[grid.y][grid.x] = 0;

				SetDrawScreen(m_backScreen);
				DrawPixel(grid.x, grid.y, 0x000000);
				SetDrawScreen(DX_SCREEN_BACK);
			}
		}
	}
}

void TitleScene::Render()
{
	// グリッド描画
	int size = Screen::WIDTH / 64;

	DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, m_backScreen, true);

	for (int i = 0; i < 64; i++)
	{
		DrawLine(i * size, 0, i * size, Screen::HEIGHT, (i % 5 == 0 ? 0x999999 : 0x555555));
	}
	for (int i = 0; i < 36; i++)
	{
		DrawLine(0, i * size, Screen::WIDTH, i * size, (i % 5 == 0 ? 0x999999 : 0x555555));
	}

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH / 2, Screen::HEIGHT / 2 - 30, 0xffffff, GetFontHandle(64), TITLE);

	m_startButton.Render();

	MyDrawFormatStringToHandleToCenter(m_startButton.GetPos().x, m_startButton.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 27), L"START");
}

void TitleScene::Finalize()
{
}

Vector2DInt TitleScene::ToGrid(Vector2D pos)
{
	return Vector2DInt{ static_cast<int>(pos.x / (Screen::WIDTH / 64)), static_cast<int>(pos.y / (Screen::HEIGHT / 36)) };
}

int TitleScene::GetRandColor()
{
	int random = GetRand(10001);

	if (random <= 8000) return Cell::COLORS[{TYPE_WIRE, SUBTYPE_NORMAL}];

	if (random <= 9000) return Cell::COLORS[{TYPE_WIRE, SUBTYPE_CROSS}];

	if (random <= 9250) return Cell::COLORS[{TYPE_INPUT, SUBTYPE_AND}];

	if (random <= 9500) return Cell::COLORS[{TYPE_INPUT, SUBTYPE_OR}];

	if (random <= 9725) return Cell::COLORS[{TYPE_OUTPUT, SUBTYPE_NORMAL}];

	if (random <= 9950) return Cell::COLORS[{TYPE_OUTPUT, SUBTYPE_NOT}];

	if (random == 9999) return Cell::COLORS[{TYPE_OTHERS, SUBTYPE_INPUT}];

	return Cell::COLORS[{TYPE_INPUT, SUBTYPE_BUTTON}];
}
