#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.cpp"
#include "Scene.cpp"
#include "Sprite.cpp"
#include "ControlledObject.cpp"
#include "WinningDoor.cpp"
#include "LoosingDoor.cpp"
#include "Window.cpp"
#include "Camera.cpp"
#include "Label.cpp"
#include "ResourceManager.cpp"

#include "MazeLoader.cpp"

using namespace std;

int main(void) {
    // init window

    Window::setName("2D Game");
    Window::setResolution(1024, 768);
    Window::open();

    // prepare resources

    ResourceManager::loadTexture("assets/textures/floor/center_001.png");
    ResourceManager::loadTexture("assets/textures/walls/wall_001.png");
    ResourceManager::loadTexture("assets/items/empty_door.png");
    ResourceManager::loadTexture("assets/items/door.png");
    ResourceManager::loadTexture("assets/main_character/main.png");

    // add intro scene

    Scene* introScene = new Scene(true);

    Label* introLabel = new Label("Wake the fuck up, samurai.", "assets/fonts/arial.ttf", 32, glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec2(100.f, 100.f), 3);
    Label* actionLabel = new Label("Press enter to start the game.", "assets/fonts/arial.ttf", 32, glm::vec4(1.f, 0.f, 1.f, 1.f), glm::vec2(100.f, 140.f), 3);

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

    // add map to scene

    vector<vector<char>> mazeMap = MazeLoader::getMazeTilemap();

    for (uint8_t i = 0; i < mazeMap.size(); i++) {
        for (uint8_t j = 0; j < mazeMap[i].size(); j++) {
            Sprite* tile;

            switch (mazeMap[i][j]) {
                case '.':
                    tile = new Tile(
                        ResourceManager::getTexture("assets/textures/floor/center_001.png"),
                        glm::vec2(j * 72.f, i * 72.f),
                        0,
                        true
                    );
                    break;
                case '#':
                    tile = new Tile(
                        ResourceManager::getTexture("assets/textures/walls/wall_001.png"),
                        glm::vec2(j * 72.f, i * 72.f),
                        0,
                        false
                    );
                    break;
                case 'L':
                    levelScene->addSprite(new Tile(
                        ResourceManager::getTexture("assets/textures/floor/center_001.png"),
                        glm::vec2(j * 72.f, i * 72.f),
                        0,
                        true
                    ));

                    tile = new LoosingDoor(
                        ResourceManager::getTexture("assets/items/empty_door.png"),
                        glm::vec2(j * 72.f, i * 72.f - 42),
                        1
                    );
                    break;
                case 'W':
                    levelScene->addSprite(new Tile(
                        ResourceManager::getTexture("assets/textures/floor/center_001.png"),
                        glm::vec2(j * 72.f, i * 72.f),
                        0,
                        true
                    ));

                    tile = new WinningDoor(
                        ResourceManager::getTexture("assets/items/door.png"),
                        glm::vec2(j * 72.f, i * 72.f - 42),
                        1
                    );
                    break;
                case '@':
                    levelScene->addSprite(new Tile(
                        ResourceManager::getTexture("assets/textures/floor/center_001.png"),
                        glm::vec2(j * 72.f, i * 72.f),
                        0,
                        true
                    ));

                    tile = new ControlledObject(
                        ResourceManager::getTexture("assets/main_character/main.png"),
                        glm::vec2(j * 72.f, i * 72.f),
                        2,
                        3.0f
                    );
                    tile->setObjectId("Main character");
                    Camera::lookAt(tile);
                    break;
                default:
                    throw runtime_error("Error: unknown tile character");
            }

            levelScene->addSprite(tile);
        }
    }

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
