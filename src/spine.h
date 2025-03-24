/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <DxLib.h>
#include "dxlib_spine_c.h"
#include "spine_loader_c.h"

class DxSpine {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DxSpine() {
        atlas = nullptr;
        skeletonData = nullptr;
        spineDrawable = nullptr;
        pos = { 0.0f };
        scale = { 1.0f };
        active = true;
        visible = true;
    };

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~DxSpine() {};

    /// <summary>
    /// �A�g���X�f�[�^
    /// </summary>
    std::shared_ptr<spAtlas> atlas;

    /// <summary>
    /// �X�P���g���f�[�^
    /// </summary>
    std::shared_ptr<spSkeletonData> skeletonData;

    /// <summary>
    /// �A�j���[�V�������̔z��
    /// </summary>
    std::vector<std::string> animationNames;

    /// <summary>
    /// spine drawable
    /// </summary>
    std::shared_ptr<DxLibSpineDrawer> spineDrawable;

    /// <summary>
    /// �X�V�E�`�悪�A�N�e�B�u��
    /// </summary>
    bool active;

    /// <summary>
    /// ����Ԃ�
    /// </summary>
    bool visible;

    /// <summary>
    /// Spine�̍��W��ύX����
    /// </summary>
    /// <param name="x">x���W</param>
    /// <param name="y">y���W</param>
    DxSpine& setPosition(float x, float y);

    /// <summary>
    /// Spine�̍��W���擾����
    /// </summary>
    /// <param name="x">x���W</param>
    /// <param name="y">y���W</param>
    void getPosition(float* x, float* y) const;

    /// <summary>
    /// �傫����ύX����
    /// </summary>
    /// <param name="scaleX">x �X�P�[��</param>
    /// <param name="scaleY">y �X�P�[��</param>
    DxSpine& setScale(float scaleX, float scaleY);

    /// <summary>
    /// �傫����ύX����
    /// </summary>
    /// <param name="scale">�X�P�[��</param>
    DxSpine& setScale(float scale);

    /// <summary>
    /// �A�j���[�V�������Z�b�g����
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <param name="animationName">�A�j���[�V������</param>
    /// <param name="mixDuration"></param>
    /// <param name="loop">���[�v���邩</param>
    /// <returns>Track Entry</returns>
    spTrackEntry* setAnimation(int trackIndex, const char* animationName, float mixDuration = 0.f, bool loop = true);

    /// <summary>
    /// �A�j���[�V������ǉ�����
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <param name="animationName">�A�j���[�V������</param>
    /// <param name="mixDuration"></param>
    /// <param name="loop">���[�v���邩</param>
    /// <param name="delay">�x��</param>
    /// <returns>Track Entry</returns>
    spTrackEntry* addAnimation(int trackIndex, const char* animationName, float mixDuration = 0.f, bool loop = true, float delay = 0.f);

    /// <summary>
    /// ��̃A�j���[�V�������Z�b�g����
    /// </summary>
    /// <param name="trackIndex">x</param>
    /// <param name="mixDuration"></param>
    /// <returns>Track Entry</returns>
    spTrackEntry* setEmptyAnimation(int trackIndex, float mixDuration = 0.f) const;

    /// <summary>
    /// ��̃A�j���[�V������ǉ�����
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <param name="mixDuration"></param>
    /// <param name="delay">�x��</param>
    /// <returns>Track Entry</returns>
    spTrackEntry* addEmptyAnimation(int trackIndex, float mixDuration = 0.f, float delay = 0.f) const;

    /// <summary>
    /// ���݂̃A�j���[�V�����̏�Ԃ��擾����
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <returns>Track Entry</returns>
    spTrackEntry* getCurrentAnimation(int trackIndex) const;

    /// <summary>
    /// �X�L�����Z�b�g����
    /// </summary>
    /// <param name="skinName">�X�L����</param>
    DxSpine& setSkin(const char* skinName);

    /// <summary>
    /// �X�L�����Z�b�g����
    /// </summary>
    /// <param name="skinNames">�X�L�����̔z��</param>
    DxSpine& setSkin(const std::vector<std::string> skinNames);

    /// <summary>
    /// ��Ԃ��X�V����
    /// </summary>
    DxSpine& update();

    /// <summary>
    /// �`�悷��
    /// </summary>
    /// <param name="fDepth">�[�x</param>
    DxSpine& draw(float fDepth = 1.0f);

private:
    /// <summary>
    /// ���W
    /// </summary>
    VECTOR pos;

    /// <summary>
    /// �X�P�[��
    /// </summary>
    VECTOR scale;
};

/// <summary>
/// Spine�����[�h����(JSON)
/// </summary>
/// <param name="strAtlasPath">�A�g���X�̃p�X</param>
/// <param name="strSkelPath">JSON�̃p�X</param>
/// <param name="spine">�i�[����DxSpine�ϐ�</param>
/// <returns>0: ����A-1: �G���[</returns>
int LoadSpineJson(std::string atlasPath, std::string jsonPath, DxSpine* spine);

/// <summary>
/// Spine�����[�h����(�o�C�i��)
/// </summary>
/// <param name="strAtlasPath">�A�g���X�̃p�X</param>
/// <param name="strSkelPath">�o�C�i���̃p�X</param>
/// <param name="spine">�i�[����DxSpine�ϐ�</param>
/// <returns>0: ����A-1: �G���[</returns>
int LoadSpineBinary(std::string atlasPath, std::string skelPath, DxSpine* spine);
