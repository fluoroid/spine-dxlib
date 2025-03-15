/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
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
    /// コンストラクタ
    /// </summary>
    DxSpine() {
        atlas = nullptr;
        skeletonData = nullptr;
        spineDrawable = nullptr;
        pos = { 0.0f };
        scale = 1.0f;
    };

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DxSpine() {};

    /// <summary>
    /// アトラスデータ
    /// </summary>
    std::shared_ptr<spAtlas> atlas;

    /// <summary>
    /// スケルトンデータ
    /// </summary>
    std::shared_ptr<spSkeletonData> skeletonData;

    /// <summary>
    /// アニメーション名の配列
    /// </summary>
    std::vector<std::string> animationNames;

    /// <summary>
    /// spine drawable
    /// </summary>
    std::shared_ptr<DxLibSpineDrawer> spineDrawable;

    /// <summary>
    /// Spineの座標を変更する
    /// </summary>
    /// <param name="x">x座標</param>
    /// <param name="y">y座標</param>
    void setPosition(float x, float y);

    /// <summary>
    /// Spineの座標を取得する
    /// </summary>
    /// <param name="x">x座標</param>
    /// <param name="y">y座標</param>
    void getPosition(float* x, float* y) const;

    /// <summary>
    /// 大きさを変更する
    /// </summary>
    /// <param name="scale">スケール</param>
    void setScale(float scale);

    /// <summary>
    /// アニメーションをセットする
    /// </summary>
    /// <param name="trackIndex">track index</param>
    /// <param name="animationName">アニメーション名</param>
    /// <param name="loop">ループするか</param>
    /// <returns>0: 完了、-1: アニメーションが見つからない</returns>
    int setAnimation(int trackIndex, const char* animationName, bool loop = true);

    /// <summary>
    /// アニメーションを追加する
    /// </summary>
    /// <param name="trackIndex">track index</param>
    /// <param name="animationName">アニメーション名</param>
    /// <param name="loop">ループするか</param>
    /// <param name="delay">遅延</param>
    /// <returns>0: 完了、-1: アニメーションが見つからない</returns>
    int addAnimation(int trackIndex, const char* animationName, bool loop = true, float delay = 0.f);

    /// <summary>
    /// 空のアニメーションをセットする
    /// </summary>
    /// <param name="trackIndex">track index</param>
    /// <param name="animationName"></param>
    /// <param name="mixDuration">mix Duration</param>
    void setEmptyAnimation(int trackIndex, float mixDuration = 0.f) const;

    /// <summary>
    /// 空のアニメーションを追加する
    /// </summary>
    /// <param name="trackIndex">track index</param>
    /// <param name="mixDuration">mix Duration</param>
    /// <param name="delay">遅延</param>
    void addEmptyAnimation(int trackIndex, float mixDuration = 0.f, float delay = 0.f) const;

    /// <summary>
    /// 状態を更新する
    /// </summary>
    void update() const;

    /// <summary>
    /// 描画する
    /// </summary>
    /// <param name="fDepth">深度</param>
    void draw(float fDepth = 1.0f) const;

private:
    /// <summary>
    /// 座標
    /// </summary>
    VECTOR pos;

    /// <summary>
    /// スケール
    /// </summary>
    float scale;
};

/// <summary>
/// Spineをロードする(JSON)
/// </summary>
/// <param name="strAtlasPath">アトラスのパス</param>
/// <param name="strSkelPath">JSONのパス</param>
/// <param name="spine">格納するDxSpine変数</param>
/// <returns>0: 正常、-1: エラー</returns>
int LoadSpineJson(std::string atlasPath, std::string jsonPath, DxSpine* spine);

/// <summary>
/// Spineをロードする(バイナリ)
/// </summary>
/// <param name="strAtlasPath">アトラスのパス</param>
/// <param name="strSkelPath">バイナリのパス</param>
/// <param name="spine">格納するDxSpine変数</param>
/// <returns>0: 正常、-1: エラー</returns>
int LoadSpineBinary(std::string atlasPath, std::string skelPath, DxSpine* spine);
