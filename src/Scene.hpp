#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <set>

#include "SpriteOrderer.hpp"
#include "OpenglObject.hpp"

using namespace std;

class OpenglObject;

class Scene {
    private:
        multiset<OpenglObject*, SpriteOrderer> sprites;

    public:
        Scene();

        multiset<OpenglObject*, SpriteOrderer> getSprites(string typeId = string());
        OpenglObject* find(string spriteId);
        void addSprite(OpenglObject* sprite);
};

#endif