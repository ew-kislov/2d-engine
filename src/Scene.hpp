#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <set>
#include <map>

#include "SpriteOrderer.hpp"
#include "Sprite.hpp"
#include "Window.hpp"
#include "Label.hpp"

using namespace std;

class Sprite;

class Scene {
    private:
        multiset<Sprite*, SpriteOrderer> sprites;
        set<Label*> ui;
        map<EKey, pair<EKeyEvent, function<void(void)>>> keyHandlers;

    public:
        Scene();

        multiset<Sprite*, SpriteOrderer> getSprites(string typeId = string());
        set<Label*> getUi();
        Sprite* find(string spriteId);
        void addSprite(Sprite* sprite);
        void addUiElement(Label* label);
        void onKeyPress(EKey key, function<void(void)> handler);
        void onKeyDown(EKey key, function<void(void)> handler);
        void onKeyUp(EKey key, function<void(void)> handler);
        void runKeyHandlers();
};

#endif