#pragma once

#include <algorithm>

#include "Scene.hpp"

#include "OpenglObject.cpp"
#include "SpriteOrderer.cpp"

Scene::Scene() {
}

multiset<OpenglObject*, SpriteOrderer> Scene::getSprites(string typeId) {
    if (typeId.empty()) {
        return this->sprites;
    }

    multiset<OpenglObject*, SpriteOrderer> filteredSprites;

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

void Scene::addSprite(OpenglObject* sprite) {
    this->sprites.insert(sprite);
    sprite->scene = this;
}