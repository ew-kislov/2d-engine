#ifndef GAME_H
#define GAME_H

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenglObject.cpp"
#include "ControlledObject.hpp"
#include "Tile.hpp"
#include "Camera.hpp"

using namespace std;

enum GameState {
    MainMenu = 1,
    Running = 2,
    Paused = 3,
    Won = 4,
    Lost = 5
};

struct KeyControlsState {
    bool isEscapePressed = false;
    bool isLeftPressed = false;
    bool isRightPressed = false;
    bool isUpPressed = false;
    bool isDownPressed = false;
    bool isEnterPressed = false;

    void resetState() {
        this->isEscapePressed = false;
        this->isLeftPressed = false;
        this->isRightPressed = false;
        this->isUpPressed = false;
        this->isDownPressed = false;
        this->isEnterPressed = false;
    }

    bool isMoving() {
        return this->isLeftPressed || this->isRightPressed || this->isUpPressed || this->isDownPressed;
    }
};

class Game {
    private:
        GLFWwindow* window;

        Camera* camera;

        ControlledObject* mainCharacter;
        ControlledObject* fucker;
        vector<vector<Tile*>> map;
        vector<OpenglObject*> enemies;
        vector<OpenglObject*> items;

        GameState gameState;
        KeyControlsState keyControlsState; 

        void addMainCharacter();
        void checkInput();
        void updatePositions();
        void draw();

    public:
        Game();

        void init();
        void loadLevel();
        void runMainLoop();
};

#endif