#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.cpp"
#include "Window.cpp"

using namespace std;

int main(void) {
    Window::setName("2D Game");
    Window::setResolution(1024, 768);
    Window::open();

    Game* game = new Game();

    game->init();
    game->loadLevel();
    game->runMainLoop();

    return 0;
}
