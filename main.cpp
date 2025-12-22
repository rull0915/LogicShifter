#include "DxLib.h"
#include "Game/Game.h"

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    // スレッド数を取得
    m_threadNum = std::thread::hardware_concurrency() / 2;
    if (m_threadNum == 0) m_threadNum = 1;

    // 画面モードのセット
    SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);

    // ウインドウのタイトルを変更する
    SetMainWindowText(L"CircuitMaker");

    // ウインドウモードへ変更
    ChangeWindowMode(TRUE);

    SetAlwaysRunFlag(TRUE);

    if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
    {
        return -1;              // エラーが起きたら直ちに終了
    }

    // 乱数の種の生成
    SRand(GetNowCount());

    // フォントのロード
    AddFontResourceExW(GetAbsolutePath(L"Resources/Fonts/Makinas-4-Flat.otf").c_str(), FR_PRIVATE, NULL);

    // マウス非表示
    SetMouseDispFlag(false);

    // ゲームの初期化
    Game game;
    game.Initialize();

    // 時間計測用
    LONGLONG m_time = GetNowHiPerformanceCount();
    LONGLONG m_oldTime;

    // 描画先画面を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);

    // ループ
    while (ProcessMessage() == 0 && !game.GetEndFrag())// && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
        m_oldTime = m_time;
        m_time = GetNowHiPerformanceCount();

        // 更新処理
        game.Update(static_cast<float>(m_time - m_oldTime) / 1000000);

        // 描画処理
        game.Render();

        if (CheckHitKey(KEY_INPUT_D))
        {
            DrawFormatStringToHandle(0, 0, 0xDDDDDD, GetFontHandle(28), L"FPS: %d", static_cast<int>(1.0f / (static_cast<float>(m_time - m_oldTime) / 1000000)));
        }

        // 裏画面の内容を表画面に反映
        ScreenFlip();

        // 画面を初期化する
        ClearDrawScreen();
    }

    return 0;
}