#include "TitleScene.h"
#include "../Game/Game.h"
#include "../Game/Common/MaskManager.h"
#include "../Game/GamePlay/Logic/CellInfo.h"

TitleScene::TitleScene(Game* pGame)
	: Scene(pGame->GetSceneManager())
	, m_pGame(pGame)
	, m_startButton{ Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT / 2 + 40 }, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 10 }, false, 0x333333, true}
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

	LoadTitleMap();

	// bgmの再生
	Sound::FadeIn(Sound::Type::TitleBgm, 0.5f);
}

void TitleScene::Update(float elapsedTime)
{
	static float m_x = 0;
	m_x += elapsedTime * (DX_PI_F / 2);

	m_startButton.ChengePos({ Screen::WIDTH / 2, Screen::HEIGHT * (5.0f / 6) + 10 * sinf(m_x) });

	m_startButton.Update();

	// 右クリックされたら
	if (m_startButton.GetIsPressed())
	{
		ChangeScene("ModeSelect",
			std::make_unique<IrisTransition>(1.0f, Transition::Mode::In, 0x888888),
			std::make_unique<IrisTransition>(1.0f, Transition::Mode::Out, 0x888888));
	}

	// 背景にブロックを置く処理
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

				Sound::Play(Sound::Type::Put, DX_PLAYTYPE_BACK);
			}
		}
	}

	// 背景のブロックを消す処理
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

				Sound::Play(Sound::Type::Put, DX_PLAYTYPE_BACK);
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

	m_startButton.Render();

	MyDrawFormatStringToHandleToCenter(m_startButton.GetPos().x, m_startButton.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 20), L"START");

	MaskManager::GetInstance().CancelMask();

	DrawExtendGraph(Screen::WIDTH / 2 - 225, Screen::HEIGHT / 3 - 225, Screen::WIDTH / 2 + 225, Screen::HEIGHT / 3 + 225, m_ghIcons["Title"], true);
}

void TitleScene::Finalize()
{
	// bgmの停止
	Sound::FadeOut(Sound::Type::TitleBgm, 0.5f);
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

void TitleScene::LoadTitleMap()
{
	// ファイルのロード
	// ファイルから読み込み
	std::ifstream ifs(GetAbsolutePath(L"Resources/Datas/Title.json"));

	json stage;
	if (ifs.is_open()) ifs >> stage;
	ifs.close();

	SetDrawScreen(m_backScreen);

	Vector2DInt pos;

	//for (auto info : stage["Stage"])
	//{
	//	pos.x = info["PosX"];
	//	pos.y = info["PosY"];

	//	m_backGround[pos.y + 5][pos.x + 14] = 0xCCCCCC;

	//	DrawPixel(pos.x + 14, pos.y + 5, 0xCCCCCC);
	//}

	SetDrawScreen(DX_SCREEN_BACK);
}
