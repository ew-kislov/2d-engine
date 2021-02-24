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
    this->camera = new Camera(Window::getWidth(), Window::getHeight());
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
        "assets/main_character/Upset.png",
        glm::vec3(200.f, 360.f, 0.f),
        1,
        3.0f
    );

    ObjectPool::getInstance()->getCamera()->setTargetInitialPosition(this->mainCharacter);

    this->objects.insert((OpenglObject*)this->mainCharacter);
}

void Game::runMainLoop() {
    do {
        Window::clear();

        this->updatePositions();
        this->draw();

        Window::update();

    } while (Window::isOpened());
}

void Game::draw() {
    for(OpenglObject* object : this->objects){
        object->draw();
    }
}

void Game::updatePositions() {
    for (uint8_t i = 0; i < this->map.size(); i++) {
        for (uint8_t j = 0; j < this->map[i].size(); j++) {
            this->map[i][j]->transform();
        }
    }

    this->mainCharacter->move();
    this->mainCharacter->transform();
}