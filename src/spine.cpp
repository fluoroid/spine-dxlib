/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
*/

#include "spine.h"
#include "fps.h"

int LoadSpineJson(std::string atlasPath, std::string jsonPath, DxSpine* spine) {
    // アトラス
    spine->atlas = spine_loader_c::CreateAtlasFromFile(atlasPath.c_str(), nullptr);
    if (spine->atlas.get() == nullptr) return -1;

    // スケルトンデータ
    spine->skeletonData = spine_loader_c::ReadJsonSkeletonFromFile(jsonPath.c_str(), spine->atlas.get());
    if (spine->skeletonData.get() == nullptr) return -1;

    // drawable
    spine->spineDrawable = std::make_shared<DxLibSpineDrawer>(spine->skeletonData.get());

    // アニメーション
    for (int i = 0; i < spine->skeletonData->animationsCount; i++) {
        const std::string& strAnimationName = spine->skeletonData->animations[i]->name;
        auto iter = std::find(spine->animationNames.begin(), spine->animationNames.end(), strAnimationName);
        if (iter == spine->animationNames.cend()) {
            spine->animationNames.push_back(strAnimationName);
        }
    }
    if (spine->animationNames.empty()) return -1;

    spine->setPosition(0, 0);

    return 0;
}

int LoadSpineBinary(std::string atlasPath, std::string skelPath, DxSpine* spine) {
    // アトラス
    spine->atlas = spine_loader_c::CreateAtlasFromFile(atlasPath.c_str(), nullptr);
    if (spine->atlas.get() == nullptr) return -1;

    // スケルトンデータ
    spine->skeletonData = spine_loader_c::ReadBinarySkeletonFromFile(skelPath.c_str(), spine->atlas.get());
    if (spine->skeletonData.get() == nullptr) return -1;

    // drawable
    spine->spineDrawable = std::make_shared<DxLibSpineDrawer>(spine->skeletonData.get());

    // アニメーション
    for (int i = 0; i < spine->skeletonData->animationsCount; i++) {
        const std::string& strAnimationName = spine->skeletonData->animations[i]->name;
        auto iter = std::find(spine->animationNames.begin(), spine->animationNames.end(), strAnimationName);
        if (iter == spine->animationNames.cend()) {
            spine->animationNames.push_back(strAnimationName);
        }
    }
    if (spine->animationNames.empty()) return -1;

    spine->setPosition(0, 0);

    return 0;
}

void DxSpine::setPosition(float x, float y) {
    //float width = skeletonData->width > 0.f ? skeletonData->width : 0;
    float height = skeletonData->height > 0.f ? skeletonData->height * scale : 0;
    pos.x = x;
    pos.y = y;
    spineDrawable->skeleton->x = pos.x / scale;
    spineDrawable->skeleton->y = (pos.y + height / 2) / scale;
};

void DxSpine::getPosition(float* x, float* y) const {
    *x = pos.x;
    *y = pos.y;
};

void DxSpine::setScale(float scale) {
    this->scale = scale;
    setPosition(pos.x, pos.y);
};

int DxSpine::setAnimation(int trackIndex, const char* animationName, bool loop) {
    auto iter = std::find(animationNames.begin(), animationNames.end(), animationName);
    if (iter == animationNames.cend()) {
        return -1;
    }
    spAnimationState_setAnimationByName(spineDrawable->animationState, trackIndex, animationName, loop ? 1 : 0);
    return 0;
};

int DxSpine::addAnimation(int trackIndex, const char* animationName, bool loop, float delay) {
    auto iter = std::find(animationNames.begin(), animationNames.end(), animationName);
    if (iter == animationNames.cend()) {
        return -1;
    }
    spAnimationState_addAnimationByName(spineDrawable->animationState, trackIndex, animationName, loop ? 1 : 0, delay);
    return 0;
};

void DxSpine::setEmptyAnimation(int trackIndex, float mixDuration) const {
    spAnimationState_setEmptyAnimation(spineDrawable->animationState, trackIndex, mixDuration);
};

void DxSpine::addEmptyAnimation(int trackIndex, float mixDuration, float delay) const {
    spAnimationState_addEmptyAnimation(spineDrawable->animationState, trackIndex, mixDuration, delay);
};

void DxSpine::update() const {
    spineDrawable->update(1 / static_cast<float>(FPS::appliedFPS));
}

void DxSpine::draw(float fDepth) const {
    spineDrawable->draw(fDepth, scale);
}
