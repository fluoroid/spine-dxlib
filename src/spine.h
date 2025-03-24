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
    /// コンストラクタ
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
    /// 更新・描画がアクティブか
    /// </summary>
    bool active;

    /// <summary>
    /// 可視状態か
    /// </summary>
    bool visible;

    /// <summary>
    /// Spineの座標を変更する
    /// </summary>
    /// <param name="x">x座標</param>
    /// <param name="y">y座標</param>
    DxSpine& setPosition(float x, float y);

    /// <summary>
    /// Spineの座標を取得する
    /// </summary>
    /// <param name="x">x座標</param>
    /// <param name="y">y座標</param>
    void getPosition(float* x, float* y) const;

    /// <summary>
    /// 大きさを変更する
    /// </summary>
    /// <param name="scaleX">x スケール</param>
    /// <param name="scaleY">y スケール</param>
    DxSpine& setScale(float scaleX, float scaleY);

    /// <summary>
    /// 大きさを変更する
    /// </summary>
    /// <param name="scale">スケール</param>
    DxSpine& setScale(float scale);

    /// <summary>
    /// アニメーションをセットする
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <param name="animationName">アニメーション名</param>
    /// <param name="mixDuration"></param>
    /// <param name="loop">ループするか</param>
    /// <returns>Track Entry</returns>
    spTrackEntry* setAnimation(int trackIndex, const char* animationName, float mixDuration = 0.f, bool loop = true);

    /// <summary>
    /// アニメーションを追加する
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <param name="animationName">アニメーション名</param>
    /// <param name="mixDuration"></param>
    /// <param name="loop">ループするか</param>
    /// <param name="delay">遅延</param>
    /// <returns>Track Entry</returns>
    spTrackEntry* addAnimation(int trackIndex, const char* animationName, float mixDuration = 0.f, bool loop = true, float delay = 0.f);

    /// <summary>
    /// 空のアニメーションをセットする
    /// </summary>
    /// <param name="trackIndex">x</param>
    /// <param name="mixDuration"></param>
    /// <returns>Track Entry</returns>
    spTrackEntry* setEmptyAnimation(int trackIndex, float mixDuration = 0.f) const;

    /// <summary>
    /// 空のアニメーションを追加する
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <param name="mixDuration"></param>
    /// <param name="delay">遅延</param>
    /// <returns>Track Entry</returns>
    spTrackEntry* addEmptyAnimation(int trackIndex, float mixDuration = 0.f, float delay = 0.f) const;

    /// <summary>
    /// 現在のアニメーションの状態を取得する
    /// </summary>
    /// <param name="trackIndex"></param>
    /// <returns>Track Entry</returns>
    spTrackEntry* getCurrentAnimation(int trackIndex) const;

    /// <summary>
    /// スキンをセットする
    /// </summary>
    /// <param name="skinName">スキン名</param>
    DxSpine& setSkin(const char* skinName);

    /// <summary>
    /// スキンをセットする
    /// </summary>
    /// <param name="skinNames">スキン名の配列</param>
    DxSpine& setSkin(const std::vector<std::string> skinNames);

    /// <summary>
    /// 状態を更新する
    /// </summary>
    DxSpine& update();

    /// <summary>
    /// 描画する
    /// </summary>
    /// <param name="fDepth">深度</param>
    DxSpine& draw(float fDepth = 1.0f);

private:
    /// <summary>
    /// 座標
    /// </summary>
    VECTOR pos;

    /// <summary>
    /// スケール
    /// </summary>
    VECTOR scale;
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
