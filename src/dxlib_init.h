/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#pragma once

/// <summary>
/// ��ʂ̉��T�C�Y
/// </summary>
constexpr int SCREEN_SIZE_X = 1920;

/// <summary>
/// ��ʂ̏c�T�C�Y
/// </summary>
constexpr int SCREEN_SIZE_Y = 1080;

/// <summary>
/// DX���C�u�����̏��������s���\����
/// </summary>
struct DxLibInit {
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pWindowHandle"></param>
    DxLibInit(void* pWindowHandle = nullptr);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~DxLibInit();

    /// <summary>
    /// DX���C�u���������������ꂽ��
    /// </summary>
    int isDxLibInitialised = -1;

    /// <summary>
    /// �A�[�J�C�u�L�[
    /// </summary>
    const char archiveKey[82] = "LBuTbfd4UPbXAVMfgywQb4TyTx98aEFxQbQmDRgXbscNNxeMpub774XG3eX4s8hWmfr9Zxpu";
};
