#include "DxLib.h"
#include "Game/Game.h"

//bool hasCuda() {
//    int deviceCount = 0;
//    cudaError_t error = cudaGetDeviceCount(&deviceCount);
//    return (error == cudaSuccess && deviceCount > 0);
//}

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    // 画面モードのセット
    SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);

    // ウインドウのタイトルを変更する
    SetMainWindowText(L"RhythmDungeon");

    // ウインドウモードへ変更
    ChangeWindowMode(TRUE);

    SetAlwaysRunFlag(TRUE);

    if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
    {
        return -1;              // エラーが起きたら直ちに終了
    }

    // フォントのロード
    AddFontResourceExA("Resources/Fonts/Makinas-4-Flat.otf", FR_PRIVATE, NULL);

    // ゲームの初期化
    Game game;
    game.Initialize();

    // GPUが使えるかチェック
//    m_isCanUseGPU = hasCuda();

    // 時間計測用
    LONGLONG m_time = GetNowHiPerformanceCount();
    LONGLONG m_oldTime;

    // 描画先画面を裏画面にセット
    SetDrawScreen(DX_SCREEN_BACK);

    // ループ
    while (ProcessMessage() == 0)// && !CheckHitKey(KEY_INPUT_ESCAPE))
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

        //if(m_isCanUseGPU)
        //{
        //    DrawFormatStringToHandle(1100, 0, 0xDDDDDD, GetFontHandle(28), L"GPU使用中");
        //}
        //else
        //{
        //    DrawFormatStringToHandle(1100, 0, 0xDDDDDD, GetFontHandle(28), L"CPU使用中");
        //}

        // 裏画面の内容を表画面に反映
        ScreenFlip();

        // 画面を初期化する
        ClearDrawScreen();
    }

    return 0;
}