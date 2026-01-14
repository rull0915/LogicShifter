#include "GameSetting.h"
#include "../Game/Common/ThreadPool.h"
GameSetting::GameSetting()
	: m_bgmBar{ Screen::WIDTH / 3, Vector2D{ Screen::WIDTH / 2 - 20, Screen::HEIGHT * (2.0f / 7)}, 20, 0xCCCCCC, 0x888888}
	, m_seBar { Screen::WIDTH / 3, Vector2D{ Screen::WIDTH / 2 - 20, Screen::HEIGHT * (3.0f / 7)}, 20, 0xCCCCCC, 0x888888}
	, m_sensitivityBar { Screen::WIDTH / 3, Vector2D{ Screen::WIDTH / 2 - 20, Screen::HEIGHT * (4.0f / 7)}, 20, 0xCCCCCC, 0x888888}
	, m_finishButton{ Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (6.0f / 7)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x3762AF }
	, m_isFullScreen{ false }
	, m_settingSwitch{ m_isFullScreen, Vector2D{ Screen::WIDTH * (4.0f / 7), Screen::HEIGHT * (5.0f / 7)},  Vector2D{ Screen::WIDTH / 14, Screen::HEIGHT / 20 } }
{
	m_bgmBar.SetResult(1.0f);
	m_seBar.SetResult(1.0f);
	m_seBar.SetResult(0.7f);
}

void GameSetting::Initialize()
{
	m_isActive = false;
}

void GameSetting::Update(float elapsedTime)
{
	if (!m_isActive) return;

	// スライドバーの更新
	m_bgmBar.Update();
	m_seBar.Update();
	m_sensitivityBar.Update();

	// 音量の設定
	Sound::ChangeVolumeAllBGM(m_bgmBar.GetResult() * 10);
	Sound::ChangeVolumeAllSE(m_seBar.GetResult() * 10);

	// 感度の更新
	m_mouseSensitivity = m_sensitivityBar.GetResult() * 1.3f + 0.2f;

	// 終了ボタンの更新
	m_finishButton.Update();

	// スイッチの更新
	bool old = m_isFullScreen;
	m_settingSwitch.Update(elapsedTime);

	if(old != m_isFullScreen)
	{
		SetChangeScreenModeGraphicsSystemResetFlag(false);

		ChangeWindowMode(!m_isFullScreen);
	}

	// 終了ボタンが押されたら
	if(m_finishButton.GetIsPressed())
	{
		// 非アクティブに
		m_isActive = false;
	}
}

void GameSetting::Render()
{
	if (!m_isActive) return;

	// 画面を暗く
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 設定の文字列
	MyDrawRoundBoxAA({ Screen::WIDTH * (1.0f / 4), Screen::HEIGHT * (1.0f / 16) }, { Screen::WIDTH * (3.0f / 4), Screen::HEIGHT * (3.0f / 16) }, 10, 0xAAAAAA, true);

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH / 2, Screen::HEIGHT / 8, 0x000000, GetFontHandle(Screen::HEIGHT / 12), L"設定");

	// スライドバーの描画
	MyDrawFormatStringToHandleToCenter( Screen::WIDTH / 2, Screen::HEIGHT * (2.0f / 7) - 32, 0xffffff, GetFontHandle(32), L"BGM Volume");
	MyDrawFormatStringToHandleToCenter( Screen::WIDTH / 2, Screen::HEIGHT * (3.0f / 7) - 32, 0xffffff, GetFontHandle(32), L"SE Volume");
	MyDrawFormatStringToHandleToCenter( Screen::WIDTH / 2, Screen::HEIGHT * (4.0f / 7) - 32, 0xffffff, GetFontHandle(32), L"マウス感度");
	m_bgmBar.Render();
	m_seBar.Render();
	m_sensitivityBar.Render();

	std::wstring bgmVal = std::to_wstring(static_cast<int>(m_bgmBar.GetResult() * 100));
	std::wstring seVal = std::to_wstring(static_cast<int>(m_seBar.GetResult() * 100));
	std::wstring senVal = std::to_wstring(static_cast<float>(m_sensitivityBar.GetResult() * 1.3f + 0.2f));
	
	senVal.erase(senVal.begin() + 3, senVal.begin() + senVal.size());

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (3.0f / 4) + 32, Screen::HEIGHT * (2.0f / 7), 0xffffff, GetFontHandle(32), bgmVal.c_str());
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (3.0f / 4) + 32, Screen::HEIGHT * (3.0f / 7), 0xffffff, GetFontHandle(32), seVal.c_str());
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (3.0f / 4) + 32, Screen::HEIGHT * (4.0f / 7), 0xffffff, GetFontHandle(32), senVal.c_str());

	// スイッチの描画
	m_settingSwitch.Render();

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (3.0f / 7), Screen::HEIGHT * (5.0f / 7), 0xffffff, GetFontHandle(32), L"FullScreen : ");

	// 終了ボタンの描画
	m_finishButton.Render();
	MyDrawFormatStringToHandleToCenter(m_finishButton.GetPos().x, m_finishButton.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"Return");
}
