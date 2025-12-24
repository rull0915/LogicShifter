#include "ResultScene.h"
#include "../Game/Game.h"

ResultScene::ResultScene(Game* pGame)
	: Scene(pGame->GetSceneManager())
	, m_pGame(pGame)
	, m_stageName{}
	, m_secondConditionValue{ -1 }
	, m_thirdConditionValue{ -1 }
	, m_thirdConditionStr{}
	, m_isSatisfied{ false, false, false }
	, m_thirdConditionID{ -1 }
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	// 情報の取得
	m_stageName = ResultInfo::GetInstance().GetStageName();
	m_secondConditionValue = ResultInfo::GetInstance().GetSecondConditionValue();
	m_thirdConditionValue = ResultInfo::GetInstance().GetThirdConditionValue();
	m_thirdConditionStr = ResultInfo::GetInstance().GetThirdCondition();

	for(int i = 0; i < 3; i++)
	{
		m_isSatisfied[i] = ResultInfo::GetInstance().GetIsSatisfied(i);
	}

	for(int i = 0; i < THIRD_CONDITIONS.size(); i++)
	{
		if (m_thirdConditionStr == THIRD_CONDITIONS[i]) m_thirdConditionID = i;
	}

	Sound::Play(Sound::Type::Clear, DX_PLAYTYPE_BACK);
	Sound::FadeIn(Sound::Type::GamePlayBgm, 0.5f);
}

void ResultScene::Update(float elapsedTime)
{
	if (MouseUp() & MOUSE_INPUT_LEFT)
	{
		ChangeScene("Select",
			std::make_unique<SlideTransition>(0.5f, Transition::Mode::In, 0x666666, ToRadian(30)),
			std::make_unique<SlideTransition>(0.5f, Transition::Mode::Out, 0x666666, ToRadian(-150)));

		Sound::Play(Sound::Type::Decide, DX_PLAYTYPE_BACK);
	}
}

void ResultScene::Render()
{
	// 背景の描画
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, 0x333F50, true);

	// ステージ名の描画
	// 背景
	DrawBox(0, Screen::HEIGHT * (1.0f / 16), Screen::WIDTH * (5.0f / 8), Screen::HEIGHT * (3.0f / 16), 0xAFABAB, true);

	// 文字列
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (5.0f / 16), Screen::HEIGHT * (2.0f / 16), 0x000000, GetFontHandle(Screen::HEIGHT * (1.0f / 16)), m_stageName.c_str());

	// 星の描画
	// 背景
	DrawBox(Screen::WIDTH * (2.0f / 8), Screen::HEIGHT * (2.0f / 8), Screen::WIDTH * (6.0f / 8), Screen::HEIGHT * (4.0f / 8), 0x222A35, true);

	// 星
	MyDrawStar({ Screen::WIDTH * (13.0f / 36), Screen::HEIGHT * (3.0f / 8) }, Screen::HEIGHT / 12, Screen::HEIGHT / 30, (m_isSatisfied[0] ? 0xFFE699 : 0x595959), true);
	MyDrawStar({ Screen::WIDTH * (18.0f / 36), Screen::HEIGHT * (3.0f / 8) }, Screen::HEIGHT / 12, Screen::HEIGHT / 30, (m_isSatisfied[1] ? 0xFFE699 : 0x595959), true);
	MyDrawStar({ Screen::WIDTH * (23.0f / 36), Screen::HEIGHT * (3.0f / 8) }, Screen::HEIGHT / 12, Screen::HEIGHT / 30, (m_isSatisfied[2] ? 0xFFE699 : 0x595959), true);

	// 条件の描画
	// 背景
	DrawBox(Screen::WIDTH * (0.0f / 8), Screen::HEIGHT * (5.0f / 8), Screen::WIDTH * (8.0f / 8), Screen::HEIGHT * (8.0f / 8), 0x3F4E63, true);

	int fontSize = Screen::HEIGHT / 24;

	// 1つ目
	MyDrawStar({ Screen::WIDTH * (2.0f / 8) + 26, Screen::HEIGHT * (6.0f / 8) - 26 }, 24, 10, 0xFFF2CC, true);
	DrawFormatStringToHandle(Screen::WIDTH * (2.0f / 8) + 100, Screen::HEIGHT * (6.0f / 8) - 26 - fontSize / 2, 0xffffff, GetFontHandle(fontSize), L"クリアで獲得");

	// 2つ目
	MyDrawStar({ Screen::WIDTH * (2.0f / 8) + 26, Screen::HEIGHT * (13.0f / 16) }, 24, 10, 0xFFF2CC, true);
	DrawFormatStringToHandle(Screen::WIDTH * (2.0f / 8) + 100, Screen::HEIGHT * (13.0f / 16) - fontSize / 2, 0xffffff, GetFontHandle(fontSize), (L"実行回数" + std::to_wstring(m_secondConditionValue) + L"回以下").c_str());

	// 3つ目
	MyDrawStar({ Screen::WIDTH * (2.0f / 8) + 26, Screen::HEIGHT * (7.0f / 8) + 26 }, 24, 10, 0xFFF2CC, true);
	DrawFormatStringToHandle(Screen::WIDTH * (2.0f / 8) + 100, Screen::HEIGHT * (7.0f / 8) + 26 - fontSize / 2, 0xffffff, GetFontHandle(fontSize), GetThirdCondition().c_str());
}

void ResultScene::Finalize()
{
	Sound::FadeOut(Sound::Type::GamePlayBgm, 0.5f);
}

std::wstring ResultScene::GetThirdCondition()
{
	std::wstring condition;
	std::wstring value;

	switch (m_thirdConditionID)
	{
	case 0:

		switch (m_thirdConditionValue)
		{
		case 0b01010000: value = L"Wire"; break;
		case 0b01100000: value = L"Cross"; break;
		case 0b10010000: value = L"And"; break;
		case 0b10100000: value = L"Or"; break;
		case 0b11010000: value = L"Output"; break;
		case 0b11100000: value = L"Not"; break;
		default:
			break;
		}

		condition = value + L"セルを使わない";

		break;
	case 1:

		value = std::to_wstring(m_thirdConditionValue);

		condition = value + L"秒以内でクリア";
		break;

	case 2:

		value = std::to_wstring(m_thirdConditionValue);

		condition = L"置いたブロック" + value + L"個以内でクリア";

		break;

	case 3:

		value = std::to_wstring(m_thirdConditionValue);

		condition = L"置いたブロックの高さを" + value + L"以内に収めてクリア";

		break;

	case 4:

		value = std::to_wstring(m_thirdConditionValue);

		condition = L"置いたブロックの幅を" + value + L"以内に収めてクリア";

		break;

	default:
		break;
	}

	return condition;
}
