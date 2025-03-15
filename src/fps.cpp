/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#include <DxLib.h>
#include "fps.h"

void FPS::update() {
    // 1�t���[���ڂȂ玞�����L��
    if (count == 0) {
        time = GetNowCount();
    }

    // 60�t���[���ڂȂ畽�ς��v�Z����
    if (count == samplingSize) {
        int t = GetNowCount();
        fps = 1000.f / ((t - time) / (double)samplingSize);
        count = 0;
        time = t;
    }

    count++;

}

void FPS::wait() const {
    // ������������
    int elapsedTime = GetNowCount() - time;

    // �҂ׂ�����
    int waitTime = count * 1000 / appliedFPS - elapsedTime;

    //�ҋ@
    if (waitTime > 0) {
        Sleep(waitTime);
    }
}

double FPS::get() const {
    return fps;
}
