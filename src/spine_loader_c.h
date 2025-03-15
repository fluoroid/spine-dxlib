/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#pragma once

#include <memory>
#include <spine/spine.h>

/// <summary>
/// Spine Loader
/// </summary>
namespace spine_loader_c {
    /// <summary>
    /// �t�@�C������A�g���X���쐬����
    /// </summary>
    /// <param name="filePath">�t�@�C���̃p�X</param>
    /// <param name="rendererObject"></param>
    /// <returns></returns>
    std::shared_ptr<spAtlas> CreateAtlasFromFile(const char* filePath, void* rendererObject);

    /// <summary>
    /// ����������A�g���X���쐬����
    /// </summary>
    /// <param name="atlasData"></param>
    /// <param name="atlasLength"></param>
    /// <param name="fileDirectory"></param>
    /// <param name="rendererObject"></param>
    /// <returns></returns>
    std::shared_ptr<spAtlas> CreateAtlasFromMemory(const char* atlasData, int atlasLength, const char* fileDirectory, void* rendererObject);

    /// <summary>
    /// JSON�t�@�C������X�P���g����ǂݍ���
    /// </summary>
    /// <param name="filePath">�t�@�C���̃p�X</param>
    /// <param name="atlas">�A�g���X</param>
    /// <param name="scale">�X�P�[��</param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadJsonSkeletonFromFile(const char* filePath, spAtlas* atlas, float scale = 1.f);

    /// <summary>
    /// �o�C�i���t�@�C������X�P���g����ǂݍ���
    /// </summary>
    /// <param name="filePath">�t�@�C���̃p�X</param>
    /// <param name="atlas">�A�g���X</param>
    /// <param name="scale">�X�P�[��</param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadBinarySkeletonFromFile(const char* filePath, spAtlas* atlas, float scale = 1.f);

    /// <summary>
    /// ����������X�P���g����ǂݍ���(JSON)
    /// </summary>
    /// <param name="skeletonJson"></param>
    /// <param name="atlas"></param>
    /// <param name="scale"></param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadTextSkeletonFromMemory(const char* skeletonJson, spAtlas* atlas, float scale = 1.f);

    /// <summary>
    /// ����������X�P���g����ǂݍ���(�o�C�i��)
    /// </summary>
    /// <param name="skeletonBinary"></param>
    /// <param name="skeletonLength"></param>
    /// <param name="atlas"></param>
    /// <param name="scale"></param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadBinarySkeletonFromMemory(const unsigned char* skeletonBinary, int skeletonLength, spAtlas* atlas, float scale = 1.f);
}
