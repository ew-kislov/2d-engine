#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "OpenglObject.cpp"
#include "Game.cpp"

using namespace std;

int main(void) {
    Game* game = new Game();

    game->init();
    game->loadLevel();
    game->runMainLoop();

    return 0;
}
