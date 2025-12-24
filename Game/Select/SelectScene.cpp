#include "SelectScene.h"
#include "../Game.h"

SelectScene::SelectScene(Game* pGame)
	: Scene(pGame->GetSceneManager())
	, m_pGame{ pGame }
	, m_moveButton{
		Button({Screen::WIDTH * (1.0f / 4), Screen::HEIGHT * (5.0f / 6)}, {64, 64}, true, m_ghIcons["Left"]),
		Button({Screen::WIDTH * (3.0f / 4), Screen::HEIGHT * (5.0f / 6)}, {64, 64}, true, m_ghIcons["Right"]),
	}
	, m_selectedNum{ 1 }
	, m_startButton{
		{Screen::WIDTH / 2, Screen::HEIGHT * (5.0f / 6)}, { 192, 48 }, false, 0xaaaaaa
	}
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Initialize()
{
	// 背景パーティクルの初期化
	m_particle.Initialize(ShapeType::Block, 0.1f, { {0, Screen::HEIGHT / 2},{Screen::WIDTH, Screen::HEIGHT * 1.5} }, { {40, 40},{60, 60} });

	// ステージ情報の読み込み
	std::ifstream ifs(GetAbsolutePath(L"Resources\\Datas\\StageInfo.json"));

	json info;

	if (ifs.is_open()) ifs >> info;

	ifs.close();

	m_stageFileName.clear();
	for (auto st : info["StageInfo"])
	{
		std::string utf8 = st.get<std::string>();
		m_stageFileName.push_back(utf8_to_wstring(utf8));
	}

	// ステージ名の読み込み
	for (auto fileName : m_stageFileName)
	{
		// --------- jsonに読み込み ---------- //
		std::ifstream file(GetAbsolutePath(L"Resources\\Stages\\" + fileName + L".json"));

		json stage;
		if (file.is_open())
		{
			file >> stage;

			// -------- 条件文の読み込み ----------- //
			m_stageNames.push_back(L"");

			m_stageNames[m_stageNames.size() - 1].resize(stage["ConditionString"].size());
			for (int i = 0; i < stage["ConditionString"].size(); i++)
			{
				m_stageNames[m_stageNames.size() - 1][i] = stage["ConditionString"][i];
			}

			// ------ ステージスクリーンの作成 ------- //
			m_ghScreens.push_back(MakeScreen(Screen::WIDTH / 2, Screen::HEIGHT / 2, true));

			// 描画先を変更
			SetDrawScreen(m_ghScreens[m_ghScreens.size() - 1]);

			// 背景描画
			DrawBox(0, 0, Screen::WIDTH / 2, Screen::HEIGHT / 2, 0x333333, true);

			// ブロックサイズを決める
			int stageHeight = stage["Height"];
			int stageWidth = stage["Width"];

			if (stageHeight > 0)
			{
				float blockSize = (Screen::HEIGHT / 2) / (stageHeight * 1.2);

				// ステージ
				for (int i = 0; i < stage["Stage"].size(); i++)
				{
					Vector2DInt pos = { stage["Stage"][i]["PosX"], stage["Stage"][i]["PosY"], };
					Vector2D renderPos = { pos.x * blockSize + Screen::WIDTH / 4 - (stageWidth % 2 == 0 ? 0 : blockSize / 2),
						pos.y * blockSize + Screen::HEIGHT / 4 - (stageHeight % 2 == 0 ? 0 : blockSize / 2) };

					int type = stage["Stage"][i]["Type"];
					int subType = stage["Stage"][i]["SubType"];

					DrawBox(renderPos.x, renderPos.y, renderPos.x + blockSize, renderPos.y + blockSize, Cell::COLORS[{type, subType}], true);
				}
			}
		}
		file.close();
	}

	// 描画先を戻す
	SetDrawScreen(DX_SCREEN_BACK);

	m_moveButton.first.Initialize();
	m_moveButton.second.Initialize();

	m_startButton.Initialize();

	Sound::FadeIn(Sound::Type::SelectBgm, 0.5f);
}

void SelectScene::Update(float elapsedTime)
{
	m_particle.Update(elapsedTime);

	// 移動ボタン
	m_moveButton.first.Update();
	m_moveButton.second.Update();

	if (m_selectedNum > 1 && m_moveButton.first.GetIsPressed()) m_selectedNum--;
	if (m_selectedNum < m_stageNames.size() && m_moveButton.second.GetIsPressed()) m_selectedNum++;

	// スタートボタン
	m_startButton.Update();

	if (m_startButton.GetIsPressed())
	{
		// 選んだステージファイルを設定
		m_pGame->SetStageFileName(GetAbsolutePath(L"Resources/Stages/" + m_stageFileName[m_selectedNum - 1] + L".json"));

		// ゲームプレイに移行
		ChangeScene("GamePlay",
			std::make_unique<SlideTransition>(0.5f, Transition::Mode::In, 0x666666, ToRadian(30)),
			std::make_unique<SlideTransition>(0.5f, Transition::Mode::Out, 0x666666, ToRadian(-150))
			);
	}
}

void SelectScene::Render()
{
	m_particle.Render(0x444444);

	// ボタンの描画
	m_moveButton.first.Render();
	m_moveButton.second.Render();

	m_startButton.Render();

	// スタート文字列の描画
	MyDrawFormatStringToHandleToCenter(m_startButton.GetPos().x, m_startButton.GetPos().y, 0x222222, GetFontHandle(32), L"開始");

	// ステージ番号の描画
	auto str = std::to_wstring(m_selectedNum);
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH / 2, Screen::HEIGHT * (1.0f / 12), 0xffffff, GetFontHandle(48), str.c_str());

	// ステージ画像の描画
	DrawGraph(Screen::WIDTH / 4, Screen::HEIGHT * (1.0f / 6), m_ghScreens[m_selectedNum - 1], true);
	DrawBox(Screen::WIDTH / 4, Screen::HEIGHT * (1.0f / 6), Screen::WIDTH / 4 + Screen::WIDTH / 2, Screen::HEIGHT * (1.0f / 6) + Screen::HEIGHT / 2, 0xDDDDDD, false, 5);

	// 条件文の描画
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH / 2, Screen::HEIGHT * (13.0f / 18), 0xffffff, GetFontHandle(32), m_stageNames[m_selectedNum - 1].c_str());
}

void SelectScene::Finalize()
{
	m_moveButton.first.Finalize();
	m_moveButton.second.Finalize();

	m_startButton.Finalize();

	for(int i = 0; i < m_ghScreens.size(); i++)
	{
		DeleteGraph(m_ghScreens[i]);
	}
		
	// ステージ情報
	m_stageFileName.clear();

	// お題
	m_stageNames.clear();

	// ステージのスクリーン
	m_ghScreens.clear();

	Sound::FadeOut(Sound::Type::SelectBgm, 0.5f);
}
