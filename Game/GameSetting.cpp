#include "GameSetting.h"

GameSetting::GameSetting()
	: m_bgmBar{ Screen::WIDTH / 3, Vector2D{ Screen::WIDTH / 2 - 20, Screen::HEIGHT * (2.0f / 5)}, 20, 0xCCCCCC, 0x888888}
	, m_seBar { Screen::WIDTH / 3, Vector2D{ Screen::WIDTH / 2 - 20, Screen::HEIGHT * (3.0f / 5)}, 20, 0xCCCCCC, 0x888888}
	, m_finishButton{ Vector2D{ Screen::WIDTH / 2, Screen::HEIGHT * (4.0f / 5)}, Vector2D{ Screen::WIDTH / 4, Screen::HEIGHT / 14 }, false, 0x3762AF }
{
	m_bgmBar.SetResult(1.0f);
	m_seBar.SetResult(1.0f);
}

void GameSetting::Initialize()
{
	m_isActive = false;
}

void GameSetting::Update()
{
	if (!m_isActive) return;

	// スライドバーの更新
	m_bgmBar.Update();
	m_seBar.Update();

	// 音量の設定
	Sound::ChangeVolumeAllBGM(m_bgmBar.GetResult() * 10);
	Sound::ChangeVolumeAllSE(m_seBar.GetResult() * 10);

	// 終了ボタンの更新
	m_finishButton.Update();

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
	MyDrawFormatStringToHandleToCenter( Screen::WIDTH / 2, Screen::HEIGHT * (2.0f / 5) - 32, 0xffffff, GetFontHandle(32), L"BGM Volume");
	MyDrawFormatStringToHandleToCenter( Screen::WIDTH / 2, Screen::HEIGHT * (3.0f / 5) - 32, 0xffffff, GetFontHandle(32), L"SE Volume");
	m_bgmBar.Render();
	m_seBar.Render();

	std::wstring bgmVal = std::to_wstring(static_cast<int>(m_bgmBar.GetResult() * 100));
	std::wstring seVal = std::to_wstring(static_cast<int>(m_seBar.GetResult() * 100));

	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (3.0f / 4) + 32, Screen::HEIGHT * (2.0f / 5), 0xffffff, GetFontHandle(32), bgmVal.c_str());
	MyDrawFormatStringToHandleToCenter(Screen::WIDTH * (3.0f / 4) + 32, Screen::HEIGHT * (3.0f / 5), 0xffffff, GetFontHandle(32), seVal.c_str());

	// 終了ボタンの描画
	m_finishButton.Render();
	MyDrawFormatStringToHandleToCenter(m_finishButton.GetPos().x, m_finishButton.GetPos().y, 0xffffff, GetFontHandle(Screen::HEIGHT / 24), L"Return");
}
