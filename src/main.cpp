/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
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

    // Spine
    DxSpine spine;
    LoadSpineBinary("data/spineboy.atlas", "data/spineboy-pro.skel", &spine);
    spine.setPosition(1920.f / 2.f, 1080.f / 2.f);
    spine.setAnimation(0, "idle");

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
        DrawFormatString(0, 48, GetColor(255, 255, 255), "�N���b�N: �A�j���[�V�����ύX�A�h���b�O: �ړ�");
        DrawFormatString(0, 96, GetColor(255, 255, 255), "%.1f fps", fps.get());

        // �L�[�{�[�h
        GetHitKeyStateAllEx(keyboardState);

        // ���݂̃t���[���̃}�E�X�̏��
        int iCurrentMouseState = GetMouseInput();

        // �h���b�O
        if ((iCurrentMouseState & MOUSE_INPUT_LEFT) && (iForeMouseState & MOUSE_INPUT_LEFT)) {
            GetMousePoint(&iMouseStartPos.x, &iMouseStartPos.y);
            spine.setPosition(static_cast<float>(iMouseStartPos.x), static_cast<float>(iMouseStartPos.y));
        }
        // �N���b�N
        else if ((iCurrentMouseState & MOUSE_INPUT_LEFT) && !(iForeMouseState & MOUSE_INPUT_LEFT)) {
            // �N���b�N�I�����̃}�E�X���W
            INT4 iMouseEndPos{ 0 };
            GetMousePoint(&iMouseEndPos.x, &iMouseEndPos.y);
            // �ω������}�E�X���W���擾
            int iX = iMouseEndPos.x - iMouseStartPos.x;
            int iY = iMouseEndPos.y - iMouseStartPos.y;
            // ���̏�ŃN���b�N�����ꍇ�A���̃A�j���[�V�����ɕύX
            if (iX == 0 && iY == 0) {
                spine.setAnimation(0, "run");
            }
        }

        // �A�b�v�f�[�g�ƕ`��
        spine.update();
        spine.draw();

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
