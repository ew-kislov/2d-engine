#ifndef GAME_H
#define GAME_H

#include <vector>
#include <set>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenglObject.hpp"
#include "ControlledObject.hpp"
#include "Tile.cpp"
#include "Camera.cpp"
#include "Window.cpp"
#include "Scene.cpp"

using namespace std;

struct OpenglObjectOrderer {
    bool operator ()(const OpenglObject* lhs, const OpenglObject* rhs) const {
        return lhs->getLayer() < rhs->getLayer();
    }
};

class Game {
    private:
        Camera* camera;

        ControlledObject* mainCharacter;
        vector<vector<Tile*>> map;

        std::multiset<OpenglObject*, OpenglObjectOrderer> objects;

        void addMainCharacter();
        void updatePositions();
        void draw();

    public:
        Game();

        void init();
        void loadLevel();
        void runMainLoop();
};

#endif