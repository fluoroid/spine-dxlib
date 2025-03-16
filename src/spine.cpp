/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
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
    spine->setScale(1.0);

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
    spine->setScale(1.0);

    return 0;
}

void DxSpine::setPosition(float x, float y) {
    pos.x = x;
    pos.y = y;
    spineDrawable->skeleton->x = pos.x / scale.x;
    spineDrawable->skeleton->y = pos.y / scale.y;
};

void DxSpine::getPosition(float* x, float* y) const {
    *x = pos.x;
    *y = pos.y;
};

void DxSpine::setScale(float scaleX, float scaleY) {
    scale.x = scaleX;
    scale.y = scaleY;
    setPosition(pos.x, pos.y);
};

void DxSpine::setScale(float scale) {
    this->scale.x = scale;
    this->scale.y = scale;
    setPosition(pos.x, pos.y);
};

spTrackEntry* DxSpine::setAnimation(int trackIndex, const char* animationName, float mixDuration, bool loop) {
    auto iter = std::find(animationNames.begin(), animationNames.end(), animationName);
    if (iter == animationNames.cend()) {
        return nullptr;
    }
    spTrackEntry* entry = spAnimationState_setAnimationByName(spineDrawable->animationState, trackIndex, animationName, loop ? 1 : 0);
    entry->mixDuration = mixDuration;
    return entry;
};

spTrackEntry* DxSpine::addAnimation(int trackIndex, const char* animationName, float mixDuration, bool loop, float delay) {
    auto iter = std::find(animationNames.begin(), animationNames.end(), animationName);
    if (iter == animationNames.cend()) {
        return nullptr;
    }
    spTrackEntry* entry = spAnimationState_addAnimationByName(spineDrawable->animationState, trackIndex, animationName, loop ? 1 : 0, delay);
    entry->mixDuration = mixDuration;
    return entry;
};

spTrackEntry* DxSpine::setEmptyAnimation(int trackIndex, float mixDuration) const {
    return spAnimationState_setEmptyAnimation(spineDrawable->animationState, trackIndex, mixDuration);
};

spTrackEntry* DxSpine::addEmptyAnimation(int trackIndex, float mixDuration, float delay) const {
    return spAnimationState_addEmptyAnimation(spineDrawable->animationState, trackIndex, mixDuration, delay);
};

spTrackEntry* DxSpine::getCurrentAnimation(int trackIndex) const {
    return spAnimationState_getCurrent(spineDrawable->animationState, trackIndex);
}

void DxSpine::setSkin(const char* skinName) const {
    spSkeleton_setSkinByName(spineDrawable->skeleton, skinName);
    spSkeleton_setSlotsToSetupPose(spineDrawable->skeleton);
}

void DxSpine::setSkin(const std::vector<std::string> skinNames) const {
    spSkin* combinedSkin = spSkin_create("CombinedSkin");
    if (skinNames.size() == 0) return;
    spSkeletonData_findSkin(skeletonData.get(), skinNames[0].c_str());
    for (int i = 0; i < skinNames.size(); i++) {
        std::string skinName = skinNames[i];
        auto skin = spSkeletonData_findSkin(skeletonData.get(), skinNames[i].c_str());
        if (!skin) continue;
        spSkin_addSkin(combinedSkin, skin);
    }
    spSkeleton_setSkin(spineDrawable->skeleton, combinedSkin);
    spSkeleton_setSlotsToSetupPose(spineDrawable->skeleton);
}

void DxSpine::update() const {
    if (active) {
        spineDrawable->update(1 / static_cast<float>(FPS::appliedFPS));
    }
}

void DxSpine::draw(float fDepth) const {
    if (active && visible) {
        spineDrawable->draw(fDepth, scale.x, scale.y);
    }
}
