/*
Copyright (c) 2025 Fluoroid (Syar Star Observatory)
This software is released under the MIT license.
*/

#include "spine.h"
#include "fps.h"

int LoadSpineJson(const char* atlasPath, const char* jsonPath, DxSpine* spine) {
    // アトラス
    spine->atlas = spine_loader_c::CreateAtlasFromFile(atlasPath, nullptr);
    if (spine->atlas.get() == nullptr) return -1;

    // スケルトンデータ
    spine->skeletonData = spine_loader_c::ReadJsonSkeletonFromFile(jsonPath, spine->atlas.get());
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

int LoadSpineBinary(const char* atlasPath, const char* skelPath, DxSpine* spine) {
    // アトラス
    spine->atlas = spine_loader_c::CreateAtlasFromFile(atlasPath, nullptr);
    if (spine->atlas.get() == nullptr) return -1;

    // スケルトンデータ
    spine->skeletonData = spine_loader_c::ReadBinarySkeletonFromFile(skelPath, spine->atlas.get());
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

DxSpine& DxSpine::setPosition(float x, float y) {
    pos.x = x;
    pos.y = y;
    spineDrawable->skeleton->x = pos.x / scale.x;
    spineDrawable->skeleton->y = pos.y / scale.y;
    return *this;
};

void DxSpine::getPosition(float* x, float* y) const {
    *x = pos.x;
    *y = pos.y;
};

DxSpine& DxSpine::setScale(float scaleX, float scaleY) {
    scale.x = scaleX;
    scale.y = scaleY;
    setPosition(pos.x, pos.y);
    return *this;
};

DxSpine& DxSpine::setScale(float scale) {
    this->scale.x = scale;
    this->scale.y = scale;
    setPosition(pos.x, pos.y);
    return *this;
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

DxSpine& DxSpine::setSkin(const char* skinName) {
    spSkeleton_setSkinByName(spineDrawable->skeleton, skinName);
    spSkeleton_setSlotsToSetupPose(spineDrawable->skeleton);
    return *this;
}

DxSpine& DxSpine::setSkin(const std::vector<std::string> skinNames) {
    spSkin* combinedSkin = spSkin_create("CombinedSkin");
    if (skinNames.size() == 0) return *this;
    spSkeletonData_findSkin(skeletonData.get(), skinNames[0].c_str());
    for (int i = 0; i < skinNames.size(); i++) {
        std::string skinName = skinNames[i];
        auto skin = spSkeletonData_findSkin(skeletonData.get(), skinNames[i].c_str());
        if (!skin) continue;
        spSkin_addSkin(combinedSkin, skin);
    }
    spSkeleton_setSkin(spineDrawable->skeleton, combinedSkin);
    spSkeleton_setSlotsToSetupPose(spineDrawable->skeleton);
    return *this;
}

DxSpine& DxSpine::update() {
    if (active) {
        spineDrawable->update(1 / static_cast<float>(FPS::appliedFPS));
    }
    return *this;
}

DxSpine& DxSpine::draw(float fDepth) {
    if (active && visible) {
        spineDrawable->draw(fDepth, scale.x, scale.y);
    }
    return *this;
}
