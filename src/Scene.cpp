#pragma once

#include <algorithm>

#include "Scene.hpp"

#include "Sprite.cpp"
#include "SpriteOrderer.cpp"
#include "Window.cpp"

Scene::Scene() {
}

multiset<Sprite*, SpriteOrderer> Scene::getSprites(string typeId) {
    if (typeId.empty()) {
        return this->sprites;
    }

    multiset<Sprite*, SpriteOrderer> filteredSprites;

    copy_if(
        this->sprites.begin(),
        this->sprites.end(),
        inserter(filteredSprites, filteredSprites.end()),
        [typeId](Sprite* sprite){ return sprite->getClassId() == typeId; }
    );

    return filteredSprites;
}

set<Label*> Scene::getUi() {
    return this->ui;
}

Sprite* Scene::find(string spriteId) {
    return NULL;
}

void Scene::addSprite(Sprite* sprite) {
    this->sprites.insert(sprite);
    sprite->scene = this;
}

void Scene::addUiElement(Label* label) {
    this->ui.insert(label);
}

void Scene::onKeyPress(EKey key, std::function<void(void)> handler) {
    this->keyHandlers[key] = pair<EKeyEvent, std::function<void(void)>>(EKeyEvent::PRESS, handler);
}

void Scene::onKeyDown(EKey key, std::function<void(void)> handler) {
    this->keyHandlers[key] = pair<EKeyEvent, std::function<void(void)>>(EKeyEvent::DOWN, handler);
}

void Scene::onKeyUp(EKey key, std::function<void(void)> handler) {
    this->keyHandlers[key] = pair<EKeyEvent, std::function<void(void)>>(EKeyEvent::UP, handler);
}

void Scene::runKeyHandlers() {
    map<EKey, pair<EKeyEvent, std::function<void(void)>>>::iterator it;

    for (it = this->keyHandlers.begin(); it != this->keyHandlers.end(); it++) {
        pair<EKeyEvent, std::function<void(void)>> handlerData = it->second;
        bool isHandlerTriggered;

        switch (handlerData.first) {
            case EKeyEvent::DOWN:
                isHandlerTriggered = Window::isKeyDown(it->first);
                break;
            case EKeyEvent::PRESS:
                isHandlerTriggered = Window::isKeyPressed(it->first);
                break;
            case EKeyEvent::UP:
                isHandlerTriggered = Window::isKeyUp(it->first);
                break;
            default:
                throw runtime_error("Error: nsupported key event.");
                exit(1);
        }

        if (isHandlerTriggered) {
            handlerData.second();
        }
    }
}