/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#pragma once

/// <summary>
/// FPS制御クラス
/// </summary>
class FPS {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FPS() {
        time = 0;
        count = 0;
        fps = 0;
        samplingSize = 60;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FPS() {
    }

    /// <summary>
    /// 現在のfpsを取得する
    /// </summary>
    /// <returns>現在のfps</returns>
    double get() const;

    /// <summary>
    /// 待機する
    /// </summary>
    void wait() const;

    /// <summary>
    /// fpsを更新する
    /// </summary>
    void update();

    /// <summary>
    /// 設定したFPS
    /// </summary>
    static const int appliedFPS = 60;

private:
    /// <summary>
    /// 測定開始時刻
    /// </summary>
    int time;

    /// <summary>
    /// カウンタ
    /// </summary>
    int count;

    /// <summary>
    /// fps
    /// </summary>
    double fps;

    /// <summary>
    /// 平均を取るサンプル数
    /// </summary>
    int samplingSize;
};
