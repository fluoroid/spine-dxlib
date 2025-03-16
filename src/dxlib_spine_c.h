/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#pragma once

#include <spine/spine.h>
#include <DxLib.h>

_SP_ARRAY_DECLARE_TYPE(spDxLibVertexArray, VERTEX2D);

/// <summary>
/// (Spine) �t�@�C����ǂݍ���
/// </summary>
/// <param name="path"></param>
/// <param name="length"></param>
/// <returns></returns>
char* _spUtil_readFile(const char* path, int* length);

/// <summary>
/// (Spine) �������ϊ�����
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
wchar_t* WidenPath(const char* path);

/// <summary>
/// (Spine) �e�N�X�`�����쐬����
/// </summary>
/// <param name="pAtlasPage"></param>
/// <param name="path"></param>
void _spAtlasPage_createTexture(spAtlasPage* pAtlasPage, const char* path);

/// <summary>
/// (Spine) �e�N�X�`����j������
/// </summary>
/// <param name="pAtlasPage"></param>
void _spAtlasPage_disposeTexture(spAtlasPage* pAtlasPage);

/// <summary>
/// (Spine) �`��N���X
/// </summary>
class DxLibSpineDrawer {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pSkeletonData">�X�P���g���f�[�^</param>
    DxLibSpineDrawer(spSkeletonData* pSkeletonData);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~DxLibSpineDrawer();

    /// <summary>
    /// �X�P���g��
    /// </summary>
    spSkeleton* skeleton = nullptr;

    /// <summary>
    /// animation state
    /// </summary>
    spAnimationState* animationState = nullptr;

    /// <summary>
    /// �^�C���X�P�[��
    /// </summary>
    float timeScale = 1.f;

    /// <summary>
    /// update
    /// </summary>
    /// <param name="fDelta">delta</param>
    void update(float fDelta) const;

    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="fDepth"></param>
    /// <param name="fScale"></param>
    void draw(float fDepth, float fScaleX, float fScaleY);

    /// <summary>
    /// ��Z�ς݃A���t�@�𔽓]������
    /// </summary>
    void switchPMA();

    /// <summary>
    /// �����I�Ƀu�����h���[�h���m�[�}���ɂ��邩�ǂ������g�O������
    /// </summary>
    void switchBlendModeAdoption();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="list"></param>
    /// <param name="listCount"></param>
    void setLeaveOutList(const char** list, int listCount);

private:
    /// <summary>
    /// ��Z�ς݃A���t�@
    /// </summary>
    bool isAlphaPremultiplied = false;

    /// <summary>
    /// �����I�Ƀu�����h���[�h���m�[�}���ɂ��邩
    /// </summary>
    bool isForceBlendModeNormal = false;

    /// <summary>
    /// ���[���h���W�̒��_
    /// </summary>
    spFloatArray* m_worldVertices = nullptr;

    /// <summary>
    /// DX���C�u�����p���_
    /// </summary>
    spDxLibVertexArray* m_dxLibVertices = nullptr;

    /// <summary>
    /// dxLibIndices
    /// </summary>
    spUnsignedShortArray* m_dxLibIndices = nullptr;

    /// <summary>
    /// clipper
    /// </summary>
    spSkeletonClipping* m_clipper = nullptr;

    char** m_leaveOutList = nullptr;

    int m_leaveOutListCount = 0;

    void clearLeaveOutList();

    bool isToBeLeftOut(const char* slotName) const;

};
