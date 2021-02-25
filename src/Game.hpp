#ifndef GAME_H
#define GAME_H

#include <vector>
#include <set>
#include <string>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"

using namespace std;


class Game {
    private:
        std::map<string, Scene*> scenes;
        Scene* activeScene;

        void updatePositions();
        void draw();

    public:
        Game();

        void init();
        void runMainLoop();

        void addScene(string name, Scene* scene);
        void setActiveScene(string name);
};

#endif