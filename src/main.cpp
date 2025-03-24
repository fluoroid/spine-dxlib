/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#include <locale.h>
#include <DxLib.h>
#include "dxlib_init.h"
#include "spine.h"
#include "fps.h"

/// <summary>
/// �v���O������ WinMain ����n�܂�܂�
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    // locale
    setlocale(LC_ALL, "");

    // DX���C�u����������
    DxLibInit dxLibInit;
    if (dxLibInit.isDxLibInitialised == -1) return 0;

    // fps
    FPS fps;

    // �g�O��
    bool flag = false;
    bool skinFlag = false;

    // Spine Boy
    DxSpine spineBoy;
    LoadSpineBinary("data/spineboy/spineboy.atlas", "data/spineboy/spineboy-pro.skel", &spineBoy);
    spineBoy
        .setPosition(1920.f / 2.f - 500, 1080.f / 2.f + 450)
        .setAnimation(0, "idle");

    // Mix and Match
    DxSpine mixAndMatch;
    LoadSpineBinary("data/mix-and-match/mix-and-match.atlas", "data/mix-and-match/mix-and-match-pro.skel", &mixAndMatch);
    mixAndMatch
        .setSkin("full-skins/girl")
        .setPosition(1920.f / 2.f + 500, 1080.f / 2.f + 450)
        .setAnimation(0, "idle");

    // �L�[�{�[�h
    int keyboardState[256]{ 0 };

    // �}�E�X
    INT4 iMouseStartPos{ 0 };

    // 1�t���[���O�̃}�E�X�̓��͏��
    int iForeMouseState = 0;

    // ���C�����[�v
    while (ProcessMessage() == 0) {
        // fps�v�Z
        fps.update();

        // ��ʃN���A
        ClearDrawScreen();

        // ����
        DrawFormatString(0, 0, GetColor(255, 255, 255), "�����DX���C�u������Spine��g�ݍ��񂾃T���v���ł��B");
        DrawFormatString(0, 48, GetColor(255, 255, 255), "Z: �A�j���[�V�����ύX�AS: �X�L���ύX�A�h���b�O: �ړ�");
        DrawFormatString(0, 96, GetColor(255, 255, 255), "%.1f fps", fps.get());

        // �L�[�{�[�h
        GetHitKeyStateAllEx(keyboardState);

        // ESC�L�[�ŏI��
        if (keyboardState[KEY_INPUT_ESCAPE] == 1) {
            break;
        }

        // ���݂̃t���[���̃}�E�X�̏��
        int iCurrentMouseState = GetMouseInput();

        // �h���b�O
        if ((iCurrentMouseState & MOUSE_INPUT_LEFT) && (iForeMouseState & MOUSE_INPUT_LEFT)) {
            GetMousePoint(&iMouseStartPos.x, &iMouseStartPos.y);
            spineBoy.setPosition(static_cast<float>(iMouseStartPos.x), static_cast<float>(iMouseStartPos.y));
        }
        // �L�[�{�[�h
        if (keyboardState[KEY_INPUT_Z] == 1) {
            if (!flag) {
                spineBoy.setAnimation(0, "run", 0.2f);
                mixAndMatch.setAnimation(0, "dance", 0.2f);
                flag = true;
            }
            else {
                spineBoy.setAnimation(0, "walk", 0.2f);
                mixAndMatch.setAnimation(0, "idle", 0.2f);
                flag = false;
            }
        }
        else if (keyboardState[KEY_INPUT_S] == 1) {
            if (!skinFlag) {
                std::vector<std::string> skins = { "accessories/cape-red", "clothes/dress-green", "eyelids/girly", "eyes/yellow", "hair/brown", "legs/boots-red", "nose/short", "skin-base" };
                mixAndMatch.setSkin(skins);
                skinFlag = true;
            }
            else {
                mixAndMatch.setSkin("full-skins/girl");
                skinFlag = false;
            }
        }

        // �A�b�v�f�[�g�ƕ`��
        spineBoy.update().draw();
        mixAndMatch.update().draw();

        // �}�E�X�̓��͗������X�V
        iForeMouseState = iCurrentMouseState;

        // ����ʂ�\��ʂɔ��f
        ScreenFlip();

        // fps�҂�
        fps.wait();
    }

    // �\�t�g�̏I��
    return 0;
}
