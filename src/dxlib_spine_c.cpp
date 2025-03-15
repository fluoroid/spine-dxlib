/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#include <wchar.h>
#include <spine/spine.h>
#include <spine/extension.h>
#include <DxLib.h>
#include "dxlib_spine_c.h"

_SP_ARRAY_IMPLEMENT_TYPE_NO_CONTAINS(spDxLibVertexArray, VERTEX2D)

static wchar_t* WidenPath(const char* path) {
    int iCharCode = GetUseCharCodeFormat();
    int iWcharCode = Get_wchar_t_CharCodeFormat();

    size_t nLen = strlen(path);
    wchar_t* pResult = static_cast<wchar_t*>(malloc((nLen + 1LL) * sizeof(wchar_t)));
    if (pResult == nullptr) return nullptr;
    wmemset(pResult, L'\0', nLen);

    int iLen = ConvertStringCharCodeFormat(iCharCode, path, iWcharCode, pResult);
    if (iLen == -1) {
        free(pResult);
        return nullptr;
    }

    wchar_t* pTemp = static_cast<wchar_t*>(realloc(pResult, (iLen + 1LL) * sizeof(wchar_t)));
    if (pTemp != nullptr) {
        pResult = pTemp;
    }
    *(pResult + iLen) = L'\0';
    return pResult;
}

void _spAtlasPage_createTexture(spAtlasPage* pAtlasPage, const char* path) {
    int iDxLibTexture = LoadGraph(path);
    if (iDxLibTexture == -1) return;

    if (pAtlasPage->width == 0 && pAtlasPage->height == 0) {
        int iWidth = 0;
        int iHeight = 0;
        GetGraphSize(iDxLibTexture, &iWidth, &iHeight);
        pAtlasPage->width = iWidth;
        pAtlasPage->height = iHeight;
    }

    void* p = reinterpret_cast<void*>(static_cast<unsigned long long>(iDxLibTexture));

    pAtlasPage->rendererObject = p;
}

void _spAtlasPage_disposeTexture(spAtlasPage* pAtlasPage) {
    DeleteGraph(static_cast<int>(reinterpret_cast<unsigned long long>(pAtlasPage->rendererObject)));
}

char* _spUtil_readFile(const char* path, int* length) {
    return _spReadFile(path, length);
}

DxLibSpineDrawer::DxLibSpineDrawer(spSkeletonData* pSkeletonData) {
    spBone_setYDown(1);

    m_worldVertices = spFloatArray_create(128);
    m_dxLibVertices = spDxLibVertexArray_create(128);
    m_dxLibIndices = spUnsignedShortArray_create(128);

    skeleton = spSkeleton_create(pSkeletonData);
    spAnimationStateData* pAnimationStateData = spAnimationStateData_create(pSkeletonData);
    animationState = spAnimationState_create(pAnimationStateData);
    m_clipper = spSkeletonClipping_create();
}

DxLibSpineDrawer::~DxLibSpineDrawer() {
    if (m_worldVertices != nullptr) {
        spFloatArray_dispose(m_worldVertices);
    }
    if (m_dxLibVertices != nullptr) {
        spDxLibVertexArray_dispose(m_dxLibVertices);
    }
    if (m_dxLibIndices != nullptr) {
        spUnsignedShortArray_dispose(m_dxLibIndices);
    }

    if (animationState != nullptr) {
        if (animationState->data != nullptr) {
            spAnimationStateData_dispose(animationState->data);
        }
        spAnimationState_dispose(animationState);
    }
    if (skeleton != nullptr) {
        spSkeleton_dispose(skeleton);
    }
    if (m_clipper != nullptr) {
        spSkeletonClipping_dispose(m_clipper);
    }
}

void DxLibSpineDrawer::update(float fDelta) const {
    if (skeleton == nullptr || animationState == nullptr) return;
    spSkeleton_update(skeleton, fDelta);
    spAnimationState_update(animationState, fDelta * timeScale);
    spAnimationState_apply(animationState, skeleton);
    spSkeleton_updateWorldTransform(skeleton, SP_PHYSICS_UPDATE);
}

void DxLibSpineDrawer::switchPMA() {
    isAlphaPremultiplied = !isAlphaPremultiplied;
}

void DxLibSpineDrawer::switchBlendModeAdoption() {
    isForceBlendModeNormal = !isForceBlendModeNormal;
}

void DxLibSpineDrawer::draw(float fDepth, float fScaleX, float fScaleY) {
    if (m_worldVertices == nullptr || m_clipper == nullptr || skeleton == nullptr || animationState == nullptr) return;

    if (skeleton->color.a == 0) return;

    static unsigned short quadIndices[] = { 0, 1, 2, 2, 3, 0 };

    for (int i = 0; i < skeleton->slotsCount; i++) {
        spSlot* pSlot = skeleton->drawOrder[i];
        spAttachment* pAttachment = pSlot->attachment;

        if (pAttachment == nullptr || pSlot->color.a == 0 || !pSlot->bone->active) {
            spSkeletonClipping_clipEnd(m_clipper, pSlot);
            continue;
        }

        spFloatArray* pVertices = m_worldVertices;
        float* pAttachmentUvs = nullptr;
        unsigned short* pIndices = nullptr;
        int indicesCount = 0;

        spColor* pAttachmentColor = nullptr;

        int iDxLibTexture = -1;

        if (pAttachment->type == SP_ATTACHMENT_REGION) {
            spRegionAttachment* pRegionAttachment = (spRegionAttachment*)pAttachment;
            pAttachmentColor = &pRegionAttachment->color;

            if (pAttachmentColor->a == 0) {
                spSkeletonClipping_clipEnd(m_clipper, pSlot);
                continue;
            }

            spFloatArray_setSize(pVertices, 8);
            spRegionAttachment_computeWorldVertices(pRegionAttachment, pSlot, pVertices->items, 0, 2);

            pAttachmentUvs = pRegionAttachment->uvs;
            pIndices = quadIndices;
            indicesCount = sizeof(quadIndices) / sizeof(unsigned short);

            iDxLibTexture = (static_cast<int>(reinterpret_cast<unsigned long long>(static_cast<spAtlasRegion*>(pRegionAttachment->rendererObject)->page->rendererObject)));
        }
        else if (pAttachment->type == SP_ATTACHMENT_MESH) {
            spMeshAttachment* pMeshAttachment = (spMeshAttachment*)pAttachment;
            pAttachmentColor = &pMeshAttachment->color;

            if (pAttachmentColor->a == 0) {
                spSkeletonClipping_clipEnd(m_clipper, pSlot);
                continue;
            }

            spFloatArray_setSize(pVertices, pMeshAttachment->super.worldVerticesLength);
            spVertexAttachment_computeWorldVertices(SUPER(pMeshAttachment), pSlot, 0, pMeshAttachment->super.worldVerticesLength, pVertices->items, 0, 2);

            pAttachmentUvs = pMeshAttachment->uvs;
            pIndices = pMeshAttachment->triangles;
            indicesCount = pMeshAttachment->trianglesCount;

            iDxLibTexture = (static_cast<int>(reinterpret_cast<unsigned long long>(static_cast<spAtlasRegion*>(pMeshAttachment->rendererObject)->page->rendererObject)));

        }
        else if (pAttachment->type == SP_ATTACHMENT_CLIPPING) {
            spClippingAttachment* clip = (spClippingAttachment*)pSlot->attachment;
            spSkeletonClipping_clipStart(m_clipper, pSlot, clip);
            continue;
        }
        else {
            spSkeletonClipping_clipEnd(m_clipper, pSlot);
            continue;
        }

        if (spSkeletonClipping_isClipping(m_clipper)) {
            spSkeletonClipping_clipTriangles(m_clipper, pVertices->items, pVertices->size, pIndices, indicesCount, pAttachmentUvs, 2);
            if (m_clipper->clippedTriangles->size == 0) {
                spSkeletonClipping_clipEnd(m_clipper, pSlot);
                continue;
            }
            pVertices = m_clipper->clippedVertices;
            pAttachmentUvs = m_clipper->clippedUVs->items;
            pIndices = m_clipper->clippedTriangles->items;
            indicesCount = m_clipper->clippedTriangles->size;
        }

        spColor tint = { 0.0f };
        tint.r = skeleton->color.r * pSlot->color.r * pAttachmentColor->r;
        tint.g = skeleton->color.g * pSlot->color.g * pAttachmentColor->g;
        tint.b = skeleton->color.b * pSlot->color.b * pAttachmentColor->b;
        tint.a = skeleton->color.a * pSlot->color.a * pAttachmentColor->a;

        // ˆÈ‰ºDXƒ‰ƒCƒuƒ‰ƒŠ—p‚ÌŽÀ‘•
        spDxLibVertexArray_clear(m_dxLibVertices);
        for (int ii = 0; ii < pVertices->size; ii += 2) {
            VERTEX2D dxLibVertex{};
            dxLibVertex.pos.x = pVertices->items[ii] * fScaleX;
            dxLibVertex.pos.y = pVertices->items[ii + 1LL] * fScaleY;
            dxLibVertex.pos.z = fDepth;
            dxLibVertex.rhw = 1.f;
            dxLibVertex.dif.r = (BYTE)(tint.r * 255.f);
            dxLibVertex.dif.g = (BYTE)(tint.g * 255.f);
            dxLibVertex.dif.b = (BYTE)(tint.b * 255.f);
            dxLibVertex.dif.a = (BYTE)(tint.a * 255.f);
            dxLibVertex.u = pAttachmentUvs[ii];
            dxLibVertex.v = pAttachmentUvs[ii + 1LL];
            spDxLibVertexArray_add(m_dxLibVertices, dxLibVertex);
        }

        spUnsignedShortArray_clear(m_dxLibIndices);
        for (int ii = 0; ii < indicesCount; ++ii) {
            spUnsignedShortArray_add(m_dxLibIndices, pIndices[ii]);
        }

        int dxLibBlendMode;
        switch (pSlot->data->blendMode) {
        case spBlendMode::SP_BLEND_MODE_ADDITIVE:
            dxLibBlendMode = isAlphaPremultiplied ? DX_BLENDMODE_PMA_ADD : DX_BLENDMODE_SPINE_ADDITIVE;
            break;
        case spBlendMode::SP_BLEND_MODE_MULTIPLY:
            dxLibBlendMode = DX_BLENDMODE_SPINE_MULTIPLY;
            break;
        case spBlendMode::SP_BLEND_MODE_SCREEN:
            dxLibBlendMode = DX_BLENDMODE_SPINE_SCREEN;
            break;
        default:
            dxLibBlendMode = isAlphaPremultiplied ? DX_BLENDMODE_PMA_ALPHA : DX_BLENDMODE_SPINE_NORMAL;
            break;
        }
        if (isForceBlendModeNormal) {
            dxLibBlendMode = isAlphaPremultiplied ? DX_BLENDMODE_PMA_ALPHA : DX_BLENDMODE_SPINE_NORMAL;
        }
        SetDrawBlendMode(dxLibBlendMode, 255);
        DrawPolygonIndexed2D(m_dxLibVertices->items, m_dxLibVertices->size, m_dxLibIndices->items, m_dxLibIndices->size / 3, iDxLibTexture, TRUE);

        spSkeletonClipping_clipEnd(m_clipper, pSlot);
    }

    spSkeletonClipping_clipEnd2(m_clipper);
}

void DxLibSpineDrawer::setLeaveOutList(const char** list, int listCount) {
    clearLeaveOutList();

    m_leaveOutList = CALLOC(char*, listCount);
    if (m_leaveOutList == nullptr) return;

    m_leaveOutListCount = listCount;
    for (int i = 0; i < m_leaveOutListCount; i++) {
        MALLOC_STR(m_leaveOutList[i], list[i]);
    }
}

void DxLibSpineDrawer::clearLeaveOutList() {
    if (m_leaveOutList != nullptr) {
        for (int i = 0; i < m_leaveOutListCount; i++) {
            if (m_leaveOutList[i] != nullptr) {
                FREE(m_leaveOutList[i]);
            }
        }
        FREE(m_leaveOutList);
    }
    m_leaveOutList = nullptr;
    m_leaveOutListCount = 0;
}

bool DxLibSpineDrawer::isToBeLeftOut(const char* slotName) const {
    for (int i = 0; i < m_leaveOutListCount; i++) {
        if (strcmp(slotName, m_leaveOutList[i]) == 0) {
            return true;
        }
    }
    return false;
}
