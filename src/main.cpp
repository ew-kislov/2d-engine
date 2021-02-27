#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.cpp"
#include "Scene.cpp"
#include "OpenglObject.cpp"
#include "ControlledObject.cpp"
#include "Window.cpp"
#include "Camera.cpp"
#include "Label.cpp"

using namespace std;

int main(void) {
    // init window

    Window::setName("2D Game");
    Window::setResolution(1024, 768);
    Window::open();

    // add level scene

    Scene* levelScene = new Scene();

    // // add main character to scene

    // OpenglObject* mainCharacter = new ControlledObject(
    //     "assets/main_character/Upset.png",
    //     glm::vec3(200.f, 360.f, 0.f),
    //     1,
    //     3.0f
    // );

    // levelScene->addSprite(mainCharacter);

    // Camera::lookAt(mainCharacter);

    // // add map to scene

    // ifstream mazeFile("src/maze.txt");
    // string line;

    // if (!mazeFile.is_open()){
    //     cout << "error while opening maze map" << endl;
    //     exit(1);
    // }

    // uint8_t i = 0;

    // while (getline(mazeFile, line)) {
    //     vector<char> mapLine(line.begin(), line.end());
    //     vector<Tile*> tileLine(mapLine.size());

    //     for (uint8_t j = 0; j < mapLine.size(); j++) {
    //         char* textureSource = (char*)(mapLine[j] == '.' ? "assets/textures/floor/center_001.png" : "assets/textures/walls/wall_001.png");

    //         OpenglObject* tile = new Tile(
    //             textureSource,
    //             glm::vec3(j * 72.f, i * 72.f, 0.f),
    //             0,
    //             mapLine[j] == '.' ? true : false
    //         );

    //         levelScene->addSprite(tile);
    //     }

    //     i++;
    // }

    // create game

    Game* game = new Game();

    game->addScene("Level", levelScene);
    game->setActiveScene("Level");

    game->init();
    game->runMainLoop();



    return 0;
}
