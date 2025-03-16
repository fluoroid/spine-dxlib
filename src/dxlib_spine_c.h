/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#pragma once

#include <spine/spine.h>
#include <DxLib.h>

_SP_ARRAY_DECLARE_TYPE(spDxLibVertexArray, VERTEX2D);

/// <summary>
/// (Spine) ファイルを読み込む
/// </summary>
/// <param name="path"></param>
/// <param name="length"></param>
/// <returns></returns>
char* _spUtil_readFile(const char* path, int* length);

/// <summary>
/// (Spine) 文字列を変換する
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
wchar_t* WidenPath(const char* path);

/// <summary>
/// (Spine) テクスチャを作成する
/// </summary>
/// <param name="pAtlasPage"></param>
/// <param name="path"></param>
void _spAtlasPage_createTexture(spAtlasPage* pAtlasPage, const char* path);

/// <summary>
/// (Spine) テクスチャを破棄する
/// </summary>
/// <param name="pAtlasPage"></param>
void _spAtlasPage_disposeTexture(spAtlasPage* pAtlasPage);

/// <summary>
/// (Spine) 描画クラス
/// </summary>
class DxLibSpineDrawer {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pSkeletonData">スケルトンデータ</param>
    DxLibSpineDrawer(spSkeletonData* pSkeletonData);

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~DxLibSpineDrawer();

    /// <summary>
    /// スケルトン
    /// </summary>
    spSkeleton* skeleton = nullptr;

    /// <summary>
    /// animation state
    /// </summary>
    spAnimationState* animationState = nullptr;

    /// <summary>
    /// タイムスケール
    /// </summary>
    float timeScale = 1.f;

    /// <summary>
    /// update
    /// </summary>
    /// <param name="fDelta">delta</param>
    void update(float fDelta) const;

    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="fDepth"></param>
    /// <param name="fScale"></param>
    void draw(float fDepth, float fScaleX, float fScaleY);

    /// <summary>
    /// 乗算済みアルファを反転させる
    /// </summary>
    void switchPMA();

    /// <summary>
    /// 強制的にブレンドモードをノーマルにするかどうかをトグルする
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
    /// 乗算済みアルファ
    /// </summary>
    bool isAlphaPremultiplied = false;

    /// <summary>
    /// 強制的にブレンドモードをノーマルにするか
    /// </summary>
    bool isForceBlendModeNormal = false;

    /// <summary>
    /// ワールド座標の頂点
    /// </summary>
    spFloatArray* m_worldVertices = nullptr;

    /// <summary>
    /// DXライブラリ用頂点
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
