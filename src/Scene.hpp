#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <set>
#include <map>

#include "SpriteOrderer.hpp"
#include "OpenglObject.hpp"
#include "Window.hpp"
#include "Label.hpp"

using namespace std;

class OpenglObject;

class Scene {
    private:
        multiset<OpenglObject*, SpriteOrderer> sprites;
        set<Label*> ui;
        map<EKey, function<void(void)>> keyHandlers;

    public:
        Scene();

        multiset<OpenglObject*, SpriteOrderer> getSprites(string typeId = string());
        set<Label*> getUi();
        OpenglObject* find(string spriteId);
        void addSprite(OpenglObject* sprite);
        void addUiElement(Label* label);
        void addKeyHandler(EKey key, function<void(void)> handler);
        void runKeyHandlers();
};

#endif