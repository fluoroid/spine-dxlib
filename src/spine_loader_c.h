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
    /// ファイルからアトラスを作成する
    /// </summary>
    /// <param name="filePath">ファイルのパス</param>
    /// <param name="rendererObject"></param>
    /// <returns></returns>
    std::shared_ptr<spAtlas> CreateAtlasFromFile(const char* filePath, void* rendererObject);

    /// <summary>
    /// メモリからアトラスを作成する
    /// </summary>
    /// <param name="atlasData"></param>
    /// <param name="atlasLength"></param>
    /// <param name="fileDirectory"></param>
    /// <param name="rendererObject"></param>
    /// <returns></returns>
    std::shared_ptr<spAtlas> CreateAtlasFromMemory(const char* atlasData, int atlasLength, const char* fileDirectory, void* rendererObject);

    /// <summary>
    /// JSONファイルからスケルトンを読み込む
    /// </summary>
    /// <param name="filePath">ファイルのパス</param>
    /// <param name="atlas">アトラス</param>
    /// <param name="scale">スケール</param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadJsonSkeletonFromFile(const char* filePath, spAtlas* atlas, float scale = 1.f);

    /// <summary>
    /// バイナリファイルからスケルトンを読み込む
    /// </summary>
    /// <param name="filePath">ファイルのパス</param>
    /// <param name="atlas">アトラス</param>
    /// <param name="scale">スケール</param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadBinarySkeletonFromFile(const char* filePath, spAtlas* atlas, float scale = 1.f);

    /// <summary>
    /// メモリからスケルトンを読み込む(JSON)
    /// </summary>
    /// <param name="skeletonJson"></param>
    /// <param name="atlas"></param>
    /// <param name="scale"></param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadTextSkeletonFromMemory(const char* skeletonJson, spAtlas* atlas, float scale = 1.f);

    /// <summary>
    /// メモリからスケルトンを読み込む(バイナリ)
    /// </summary>
    /// <param name="skeletonBinary"></param>
    /// <param name="skeletonLength"></param>
    /// <param name="atlas"></param>
    /// <param name="scale"></param>
    /// <returns></returns>
    std::shared_ptr<spSkeletonData> ReadBinarySkeletonFromMemory(const unsigned char* skeletonBinary, int skeletonLength, spAtlas* atlas, float scale = 1.f);
}
