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
        static std::map<string, Scene*> scenes;
        static Scene* activeScene;

        static void updatePositions();
        static void draw();

    public:
        Game();

        static void init();
        static void runMainLoop();

        static void addScene(string name, Scene* scene);
        static void setActiveScene(string name);
};

#endif