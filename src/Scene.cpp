#pragma once

#include <algorithm>

#include "Scene.hpp"

#include "OpenglObject.cpp"
#include "SpriteOrderer.cpp"
#include "Window.cpp"

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

set<Label*> Scene::getUi() {
    return this->ui;
}

OpenglObject* Scene::find(string spriteId) {
    return NULL;
}

void Scene::addSprite(OpenglObject* sprite) {
    this->sprites.insert(sprite);
    sprite->scene = this;
}

void Scene::addUiElement(Label* label) {
    this->ui.insert(label);
}

void Scene::addKeyHandler(EKey key, std::function<void(void)> handler) {
    this->keyHandlers[key] = handler;
}

void Scene::runKeyHandlers() {
    map<EKey, std::function<void(void)>>::iterator it;

    for (it = this->keyHandlers.begin(); it != this->keyHandlers.end(); it++) {
        if (Window::isKeyPressed(it->first)) {
            it->second();
        }
    }
}