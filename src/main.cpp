/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#include "DxLib.h"

/// <summary>
/// �v���O������ WinMain ����n�܂�܂�
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // applog����
    SetOutApplicationLogValidFlag(false);

    // �E�C���h�E���[�h�ŋN��
    ChangeWindowMode(TRUE);

    // �E�C���h�E�傫���ݒ�
    SetGraphMode(2560, 1440, 32);

    // �E�B���h�E���m���A�N�e�B�u�ł����s
    SetAlwaysRunFlag(TRUE);

    // ������������
    SetWaitVSyncFlag(TRUE);

    // ���d�N�����֎~����
    SetDoubleStartValidFlag(FALSE);

    // �E�C���h�E�N���X��
    SetMainWindowClassName("DXLib-Spine");

    // �E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
    //SetWindowSizeChangeEnableFlag(TRUE);

    // �`��{��
    SetWindowSizeExtendRate(0.5);

    // �A�C�R���w��
    //SetWindowIconID(IDI_ICON2);

    // �`�惂�[�h��ς��ăs�N�Z�����ڂ���
    SetDrawMode(DX_DRAWMODE_NEAREST);
    //SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);

    // �A���t�@�`�����l���̂Ȃ��摜�œ��߂��Ȃ�
    SetUseTransColor(FALSE);

    // �^�C�g���̕ύX
    SetMainWindowText("DxLib Spine");

    // �A�[�J�C�u
    SetUseDXArchiveFlag(TRUE);
    SetDXArchiveExtension("rom");
    //SetDXArchiveKeyString(P_Str);

    // DX���C�u����������
    if (DxLib_Init() == -1) {
        return -1;
    }

    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // �f�t�H���g�����T�C�Y
    SetFontSize(48);

    // ���C�����[�v
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        // �`��
        DrawBox(100, 100, 300, 300, GetColor(255, 0, 0), TRUE);

        // ����
        DrawFormatString(0, 0, GetColor(255, 255, 255), "Hello! ����ɂ��́I%d", 3);
    }

    // DX���C�u�����g�p�̏I������
    DxLib_End();

    // �\�t�g�̏I��
    return 0;
}
