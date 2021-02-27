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
#include "SpriteOrderer.cpp"
#include "ControlledObject.cpp"
#include "Tile.cpp"
#include "Camera.cpp"
#include "Window.cpp"
#include "Scene.cpp"
#include "Label.cpp"

Game::Game() {
}

void Game::init() {
    Camera::setResolution(Window::getWidth(), Window::getHeight());
}

void Game::runMainLoop() {
    Label* label = new Label("fuck you", "assets/fonts/fuck.ttf", 70, glm::vec4(1.f, 0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 0.f), 3);
    label->setPreview();
    do {
        Window::clear();

        Camera::move();

        label->transform();
        label->draw();

        // this->updatePositions();
        // this->draw();

        Window::update();

    } while (Window::isOpened());
}

void Game::draw() {
    auto sprites = this->activeScene->getSprites();

    for (OpenglObject* sprite : sprites) {
        sprite->draw();
    }
}

void Game::updatePositions() {
    auto sprites = this->activeScene->getSprites();

    for (OpenglObject* sprite : sprites) {
        sprite->move();
        sprite->transform();
    }
}

void Game::addScene(string name, Scene* scene) {
    this->scenes[name] = scene;
}

void Game::setActiveScene(string name) {
    this->activeScene = this->scenes[name];
}