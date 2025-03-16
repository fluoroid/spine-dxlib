/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#include <DxLib.h>
#include "dxlib_init.h"

DxLibInit::DxLibInit(void* pWindowHandle) {
    // applog無効
    SetOutApplicationLogValidFlag(false);

    // ウインドウモードで起動
    ChangeWindowMode(TRUE);

    // 画面モード変更時にグラフィックスシステムの設定やグラフィックハンドルをリセットしない
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // ウインドウ大きさ設定
    SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

    // ウィンドウがノンアクティブでも実行
    SetAlwaysRunFlag(TRUE);

    // 垂直同期する
    SetWaitVSyncFlag(TRUE);

    // 多重起動を禁止する
    SetDoubleStartValidFlag(FALSE);

    // ウインドウクラス名
    SetMainWindowClassName("dxlib-spine");

    // ウィンドウサイズを自由に変更できるようにする
    SetWindowSizeChangeEnableFlag(TRUE);

    // 描画倍率
    SetWindowSizeExtendRate(0.666);

    // アイコン指定
    //SetWindowIconID(IDI_ICON2);

    // アルファチャンネルのない画像で透過しない
    SetUseTransColor(FALSE);

    // タイトルの変更
    SetMainWindowText("DxLib Spine");

    // アーカイブ
    SetUseDXArchiveFlag(TRUE);
    SetDXArchiveExtension("rom");
    SetDXArchiveKeyString(archiveKey);

    // DXライブラリ初期化
    isDxLibInitialised = DxLib_Init();

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // 描画モード
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    //SetFullScreenScalingMode(DX_DRAWMODE_BILINEAR);

    // テクスチャアドレスモード
    SetTextureAddressMode(DX_TEXADDRESS_WRAP);

    // デフォルト文字サイズ
    SetFontSize(48);
}

DxLibInit::~DxLibInit() {
    if (isDxLibInitialised != -1) {
        DxLib_End();
    }
}
