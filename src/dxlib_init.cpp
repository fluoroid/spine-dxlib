/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#include <DxLib.h>
#include "dxlib_init.h"

DxLibInit::DxLibInit(void* pWindowHandle) {
    // applog����
    SetOutApplicationLogValidFlag(false);

    // �E�C���h�E���[�h�ŋN��
    ChangeWindowMode(TRUE);

    // ��ʃ��[�h�ύX���ɃO���t�B�b�N�X�V�X�e���̐ݒ��O���t�B�b�N�n���h�������Z�b�g���Ȃ�
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // �E�C���h�E�傫���ݒ�
    SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

    // �E�B���h�E���m���A�N�e�B�u�ł����s
    SetAlwaysRunFlag(TRUE);

    // ������������
    SetWaitVSyncFlag(TRUE);

    // ���d�N�����֎~����
    SetDoubleStartValidFlag(FALSE);

    // �E�C���h�E�N���X��
    SetMainWindowClassName("dxlib-spine");

    // �E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���
    SetWindowSizeChangeEnableFlag(TRUE);

    // �`��{��
    SetWindowSizeExtendRate(0.666);

    // �A�C�R���w��
    //SetWindowIconID(IDI_ICON2);

    // �A���t�@�`�����l���̂Ȃ��摜�œ��߂��Ȃ�
    SetUseTransColor(FALSE);

    // �^�C�g���̕ύX
    SetMainWindowText("DxLib Spine");

    // �A�[�J�C�u
    SetUseDXArchiveFlag(TRUE);
    SetDXArchiveExtension("rom");
    SetDXArchiveKeyString(archiveKey);

    // DX���C�u����������
    isDxLibInitialised = DxLib_Init();

    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // �`�惂�[�h
    SetDrawMode(DX_DRAWMODE_BILINEAR);
    //SetFullScreenScalingMode(DX_DRAWMODE_BILINEAR);

    // �e�N�X�`���A�h���X���[�h
    SetTextureAddressMode(DX_TEXADDRESS_WRAP);

    // �f�t�H���g�����T�C�Y
    SetFontSize(48);
}

DxLibInit::~DxLibInit() {
    if (isDxLibInitialised != -1) {
        DxLib_End();
    }
}
