#pragma once

#include <algorithm>

#include "Scene.hpp";

Scene::Scene() {
}

set<OpenglObject*, SpriteOrderer> Scene::getSprites(string typeId) {
    if (typeId.empty()) {
        return this->sprites;
    }

    set<OpenglObject*, SpriteOrderer> filteredSprites;

    copy_if(
        this->sprites.begin(),
        this->sprites.end(),
        inserter(filteredSprites, filteredSprites.end()),
        [typeId](OpenglObject* sprite){ return sprite->getClassId() == typeId; }
    );

    return filteredSprites;
}

OpenglObject* Scene::find(string spriteId) {
    return NULL;
}