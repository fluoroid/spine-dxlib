/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#include <locale.h>
#include <DxLib.h>
#include "dxlib_init.h"
#include "spine.h"
#include "fps.h"

/// <summary>
/// プログラムは WinMain から始まります
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // locale
    setlocale(LC_ALL, "");

    // DXライブラリ初期化
    DxLibInit dxLibInit;
    if (dxLibInit.isDxLibInitialised == -1) return 0;

    // fps
    FPS fps;

    // Spine
    DxSpine spine;
    LoadSpineBinary("data/spineboy.atlas", "data/spineboy-pro.skel", &spine);
    spine.setPosition(1920.f / 2.f, 1080.f / 2.f);
    spine.setAnimation(0, "idle");

    // キーボード
    int keyboardState[256]{ 0 };

    // マウス
    INT4 iMouseStartPos{ 0 };

    // 1フレーム前のマウスの入力状態
    int iForeMouseState = 0;

    // メインループ
    while (ProcessMessage() == 0) {
        // fps計算
        fps.update();

        // 画面クリア
        ClearDrawScreen();

        // 文字
        DrawFormatString(0, 0, GetColor(255, 255, 255), "これはDXライブラリにSpineを組み込んだサンプルです。");
        DrawFormatString(0, 48, GetColor(255, 255, 255), "クリック: アニメーション変更、ドラッグ: 移動");
        DrawFormatString(0, 96, GetColor(255, 255, 255), "%.1f fps", fps.get());

        // キーボード
        GetHitKeyStateAllEx(keyboardState);

        // 現在のフレームのマウスの状態
        int iCurrentMouseState = GetMouseInput();

        // ドラッグ
        if ((iCurrentMouseState & MOUSE_INPUT_LEFT) && (iForeMouseState & MOUSE_INPUT_LEFT)) {
            GetMousePoint(&iMouseStartPos.x, &iMouseStartPos.y);
            spine.setPosition(static_cast<float>(iMouseStartPos.x), static_cast<float>(iMouseStartPos.y));
        }
        // クリック
        else if ((iCurrentMouseState & MOUSE_INPUT_LEFT) && !(iForeMouseState & MOUSE_INPUT_LEFT)) {
            // クリック終了時のマウス座標
            INT4 iMouseEndPos{ 0 };
            GetMousePoint(&iMouseEndPos.x, &iMouseEndPos.y);
            // 変化したマウス座標を取得
            int iX = iMouseEndPos.x - iMouseStartPos.x;
            int iY = iMouseEndPos.y - iMouseStartPos.y;
            // その場でクリックした場合、次のアニメーションに変更
            if (iX == 0 && iY == 0) {
                spine.setAnimation(0, "run");
            }
        }

        // アップデートと描画
        spine.update();
        spine.draw();

        // マウスの入力履歴を更新
        iForeMouseState = iCurrentMouseState;

        // 裏画面を表画面に反映
        ScreenFlip();

        // fps待ち
        fps.wait();
    }

    // ソフトの終了
    return 0;
}
