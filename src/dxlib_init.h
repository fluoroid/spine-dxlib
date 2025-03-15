/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#pragma once

/// <summary>
/// 画面の横サイズ
/// </summary>
constexpr int SCREEN_SIZE_X = 1920;

/// <summary>
/// 画面の縦サイズ
/// </summary>
constexpr int SCREEN_SIZE_Y = 1080;

/// <summary>
/// DXライブラリの初期化を行う構造体
/// </summary>
struct DxLibInit {
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pWindowHandle"></param>
    DxLibInit(void* pWindowHandle = nullptr);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DxLibInit();

    /// <summary>
    /// DXライブラリが初期化されたか
    /// </summary>
    int isDxLibInitialised = -1;

    /// <summary>
    /// アーカイブキー
    /// </summary>
    const char archiveKey[82] = "LBuTbfd4UPbXAVMfgywQb4TyTx98aEFxQbQmDRgXbscNNxeMpub774XG3eX4s8hWmfr9Zxpu";
};
