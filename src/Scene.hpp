#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <set>

#include "OpenglObject.hpp";

using namespace std;


struct SpriteOrderer {
    bool operator()(const OpenglObject* lhs, const OpenglObject* rhs) const {
        return lhs->getLayer() < rhs->getLayer();
    }
};


class Scene {
    private:
        set<OpenglObject*, SpriteOrderer> sprites;

    public:
        Scene();

        set<OpenglObject*, SpriteOrderer> getSprites(string typeId = string());
        OpenglObject* find(string spriteId);
};

#endif