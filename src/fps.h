/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#pragma once

/// <summary>
/// FPS����N���X
/// </summary>
class FPS {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FPS() {
        time = 0;
        count = 0;
        fps = 0;
        samplingSize = 60;
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FPS() {
    }

    /// <summary>
    /// ���݂�fps���擾����
    /// </summary>
    /// <returns>���݂�fps</returns>
    double get() const;

    /// <summary>
    /// �ҋ@����
    /// </summary>
    void wait() const;

    /// <summary>
    /// fps���X�V����
    /// </summary>
    void update();

    /// <summary>
    /// �ݒ肵��FPS
    /// </summary>
    static const int appliedFPS = 60;

private:
    /// <summary>
    /// ����J�n����
    /// </summary>
    int time;

    /// <summary>
    /// �J�E���^
    /// </summary>
    int count;

    /// <summary>
    /// fps
    /// </summary>
    double fps;

    /// <summary>
    /// ���ς����T���v����
    /// </summary>
    int samplingSize;
};
