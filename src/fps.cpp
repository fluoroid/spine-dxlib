/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#include <DxLib.h>
#include "fps.h"

void FPS::update() {
    // 1フレーム目なら時刻を記憶
    if (count == 0) {
        time = GetNowCount();
    }

    // 60フレーム目なら平均を計算する
    if (count == samplingSize) {
        int t = GetNowCount();
        fps = 1000.f / ((t - time) / (double)samplingSize);
        count = 0;
        time = t;
    }

    count++;

}

void FPS::wait() const {
    // かかった時間
    int elapsedTime = GetNowCount() - time;

    // 待つべき時間
    int waitTime = count * 1000 / appliedFPS - elapsedTime;

    //待機
    if (waitTime > 0) {
        Sleep(waitTime);
    }
}

double FPS::get() const {
    return fps;
}
