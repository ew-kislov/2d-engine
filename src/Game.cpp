#pragma once

#include "Game.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "OpenglObject.cpp"
#include "ControlledObject.cpp"
#include "Camera.cpp"

Game::Game() {
}

void Game::init() {
    this->window = OpenglUtils::initWindow();

    this->camera = new Camera();
    this->camera->setProjection(MathUtils::projectionMatrix);
}

void Game::loadLevel() {
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

            Tile* tile = new Tile(
                "src/vertex_shader.glsl",
                "src/fragment_shader.glsl",
                textureSource,
                glm::vec3(j * 72.f, i * 72.f, 0.f),
                0,
                mapLine[j] == '.' ? true : false
            );

            tileLine[j] = tile;
            this->objects.insert((OpenglObject*)tile);
        }

        this->map.push_back(tileLine);

        i++;
    }

    this->addMainCharacter();
}

void Game::addMainCharacter() {
    this->mainCharacter = new ControlledObject(
        "src/vertex_shader.glsl",
        "src/fragment_shader.glsl",
        "assets/main_character/idle_000.png",
        glm::vec3(200.f, 360.f, 0.f),
        1,
        3.0f
    );

    ObjectPool::getInstance()->getCamera()->setTargetInitialPosition(this->mainCharacter);

    this->objects.insert((OpenglObject*)this->mainCharacter);
}

void Game::runMainLoop() {
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->checkInput();
        this->updatePositions();
        this->draw();

        glfwSwapBuffers(this->window);
        glfwPollEvents();

    } while (glfwWindowShouldClose(this->window) == 0);
}

void Game::draw() {
    for(OpenglObject* object : this->objects){
        object->draw();
    }
}

void Game::checkInput() {
    this->keyControlsState.resetState();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->keyControlsState.isUpPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->keyControlsState.isDownPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        this->keyControlsState.isLeftPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        this->keyControlsState.isRightPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        this->keyControlsState.isEscapePressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        this->keyControlsState.isEnterPressed = true;
    }
}

void Game::updatePositions() {
    for (uint8_t i = 0; i < this->map.size(); i++) {
        for (uint8_t j = 0; j < this->map[i].size(); j++) {
            this->map[i][j]->transform();
        }
    }

    if (this->keyControlsState.isMoving()) {
        this->mainCharacter->move(glm::vec3(
            this->keyControlsState.isLeftPressed ? -1.0 : this->keyControlsState.isRightPressed ? 1.0 : 0.0,
            this->keyControlsState.isUpPressed ? -1.0 : this->keyControlsState.isDownPressed ? 1.0 : 0.0,
            0.0
        ));
    }

    this->mainCharacter->transform();
}