#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.cpp"
#include "Scene.cpp"
#include "Sprite.cpp"
#include "ControlledObject.cpp"
#include "WinningDoor.cpp"
#include "Window.cpp"
#include "Camera.cpp"
#include "Label.cpp"

using namespace std;

int main(void) {
    // init window

    Window::setName("2D Game");
    Window::setResolution(1024, 768);
    Window::open();

    // add intro scene

    Scene* introScene = new Scene(true);

    Label* introLabel = new Label("Wake the fuck up, samurai.", "assets/fonts/arial.ttf", 32, glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec2(100.f, 100.f), 3);
    Label* actionLabel = new Label("Press enter to start the game.", "assets/fonts/arial.ttf", 32, glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec2(100.f, 120.f), 3);

    introScene->addUiElement(introLabel);
    introScene->addUiElement(actionLabel);

    introScene->onKeyDown(EKey::Enter, []() { Game::setActiveScene("Level"); });

    // add pause scene

    Scene* pauseScene = new Scene(true);

    Label* pauseLabel = new Label("Press P to resume the game.", "assets/fonts/arial.ttf", 32, glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec2(100.f, 100.f), 3);

    pauseScene->addUiElement(pauseLabel);

    pauseScene->onKeyDown(EKey::P, []() { Game::setActiveScene("Level"); });

    // add game over scene

    Scene* gameOverScene = new Scene(true);

    Label* gameOverLabel = new Label("You`r fucked. Press enter for main menu", "assets/fonts/arial.ttf", 32, glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec2(100.f, 100.f), 3);

    gameOverScene->addUiElement(gameOverLabel);

    gameOverScene->onKeyDown(EKey::Enter, []() { Game::setActiveScene("Intro"); });

    // add game over scene

    Scene* winScene = new Scene(true);

    Label* winLabel = new Label("You fucking won. Press enter for main menu", "assets/fonts/arial.ttf", 32, glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec2(100.f, 100.f), 3);

    winScene->addUiElement(winLabel);

    winScene->onKeyDown(EKey::Enter, []() { Game::setActiveScene("Intro"); });

    // add level scene

    Scene* levelScene = new Scene(false);

    levelScene->onKeyDown(EKey::P, []() { Game::setActiveScene("Pause"); });

    // add main character to scene

    Sprite* mainCharacter = new ControlledObject(
        "assets/main_character/Upset.png",
        glm::vec2(200.f, 360.f),
        2,
        3.0f
    );

    mainCharacter->setObjectId("Main character");

    levelScene->addSprite(mainCharacter);

    Camera::lookAt(mainCharacter);

    // add map to scene

    ifstream mazeFile("src/maze.txt");
    string line;

    if (!mazeFile.is_open()){
        cout << "error while opening maze map" << endl;
        exit(1);
    }

    uint8_t i = 0;

    while (getline(mazeFile, line)) {
        vector<char> mapLine(line.begin(), line.end());
        vector<Tile*> tileLine(mapLine.size());

        for (uint8_t j = 0; j < mapLine.size(); j++) {
            char* textureSource = (char*)(mapLine[j] == '.' ? "assets/textures/floor/center_001.png" : "assets/textures/walls/wall_001.png");

            Sprite* tile = new Tile(
                textureSource,
                glm::vec2(j * 72.f, i * 72.f),
                0,
                mapLine[j] == '.' ? true : false
            );

            levelScene->addSprite(tile);
        }

        i++;
    }


    Sprite* door = new WinningDoor(
        "assets/items/door.png",
        glm::vec2(576, 390),
        1
    );

    levelScene->addSprite(door);

    // init game


    Game::addScene("Level", levelScene);
    Game::addScene("Intro", introScene);
    Game::addScene("Pause", pauseScene);
    Game::addScene("Game Over", gameOverScene);
    Game::addScene("Win", winScene);

    Game::setActiveScene("Intro");
    Game::init();
    Game::runMainLoop();

    return 0;
}
