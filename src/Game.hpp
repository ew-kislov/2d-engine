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
        static std::map<string, shared_ptr<Scene> > scenes;
        static shared_ptr<Scene> activeScene;

        static bool shouldChangeScene;
        static string nextScene;

        static int framesPerSec;
        static double lastFpsUpdateTime;
        static double lastTime;
        static double deltaTime;

        static void calculateFps();

        static void switchScene();

        static void updatePositions();
        static void draw();

    public:
        Game();

        static void init();
        static void runMainLoop();

        static void addScene(shared_ptr<Scene> scene);
        static shared_ptr<Scene> getScene(string name);

        static void setActiveScene(string name);
        static void loadScene(string name);
};

#endif