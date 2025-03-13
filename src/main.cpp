/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#include "DxLib.h"

/// <summary>
/// プログラムは WinMain から始まります
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // applog無効
    SetOutApplicationLogValidFlag(false);

    // ウインドウモードで起動
    ChangeWindowMode(TRUE);

    // ウインドウ大きさ設定
    SetGraphMode(2560, 1440, 32);

    // ウィンドウがノンアクティブでも実行
    SetAlwaysRunFlag(TRUE);

    // 垂直同期する
    SetWaitVSyncFlag(TRUE);

    // 多重起動を禁止する
    SetDoubleStartValidFlag(FALSE);

    // ウインドウクラス名
    SetMainWindowClassName("DXLib-Spine");

    // ウィンドウサイズを自由に変更できるようにする
    //SetWindowSizeChangeEnableFlag(TRUE);

    // 描画倍率
    SetWindowSizeExtendRate(0.5);

    // アイコン指定
    //SetWindowIconID(IDI_ICON2);

    // 描画モードを変えてピクセルをぼかす
    SetDrawMode(DX_DRAWMODE_NEAREST);
    //SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);

    // アルファチャンネルのない画像で透過しない
    SetUseTransColor(FALSE);

    // タイトルの変更
    SetMainWindowText("DxLib Spine");

    // アーカイブ
    SetUseDXArchiveFlag(TRUE);
    SetDXArchiveExtension("rom");
    //SetDXArchiveKeyString(P_Str);

    // DXライブラリ初期化
    if (DxLib_Init() == -1) {
        return -1;
    }

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // デフォルト文字サイズ
    SetFontSize(48);

    // メインループ
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        // 描画
        DrawBox(100, 100, 300, 300, GetColor(255, 0, 0), TRUE);

        // 文字
        DrawFormatString(0, 0, GetColor(255, 255, 255), "Hello! こんにちは！%d", 3);
    }

    // DXライブラリ使用の終了処理
    DxLib_End();

    // ソフトの終了
    return 0;
}
